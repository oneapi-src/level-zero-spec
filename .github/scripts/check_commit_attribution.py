#!/usr/bin/env python3
"""Fail if commits credit anyone other than a human with an allowed email domain.

Exit codes: 0 = clean, 1 = problems found, 2 = the check could not run.
"""
import argparse
import os
import re
import subprocess
import sys

ALLOWED_DOMAINS = {"intel.com"}
# Bots that may author commits. Their own trailers skip the domain rule.
ALLOWED_BOTS = {
    "49699333+dependabot[bot]@users.noreply.github.com",
    "41898282+github-actions[bot]@users.noreply.github.com",
}
# Committer GitHub uses for web-UI edits and "Update branch" merges.
GITHUB_WEB_FLOW = "noreply@github.com"

AI_RE = re.compile(
    r"(?<![a-z0-9])("
    r"claude|anthropic|copilot|chatgpt|openai|gpt-\d[\w.]*|gemini|codex|"
    r"codeium|windsurf|tabnine|aider|codewhisperer|amazon\s+q|deepseek|qwen|"
    r"mistral|llama|cursor\s+(?:ai|agent)|llm|large\s+language\s+model|"
    r"ai[- ](?:assisted|generated|agent|assistant|tool)|generated\s+(?:with|by)\s+ai"
    r")(?![a-z0-9])"
    r"|\U0001F916",
    re.IGNORECASE,
)
TRAILER_RE = re.compile(r"^([A-Za-z][A-Za-z0-9-]*-by)\s*:\s*(.*)$", re.IGNORECASE)
# Squash merges append " (#123)" to the subject line.
IDENT_RE = re.compile(r"^[^<>]+?\s*<([^<>\s]+@[^<>\s]+)>(?:\s*\(#\d+\))?$")
DOMAINS_TEXT = " or ".join("@" + d for d in sorted(ALLOWED_DOMAINS))
PR_TEXT_LABEL = "PR title / description"


def domain_ok(email):
    return email.lower().rsplit("@", 1)[-1] in ALLOWED_DOMAINS


def check_message(text, bot=False):
    problems = []
    for line in text.splitlines():
        s = line.strip().replace("`", "'")
        m = TRAILER_RE.match(s)
        if m:
            key, value = m.groups()
            ident = IDENT_RE.match(value)
            if AI_RE.search(value):
                problems.append(f"`{key}` names an AI tool: {s}")
            elif bot:
                pass
            elif not ident:
                problems.append(f"`{key}` must be `Name <you{DOMAINS_TEXT}>`: {s}")
            elif not domain_ok(ident.group(1)):
                problems.append(f"`{key}` email is not {DOMAINS_TEXT}: {s}")
        elif AI_RE.search(s):
            problems.append(f"mentions an AI tool: {s}")
    return problems


def check_identity(role, name, email, extra_ok=()):
    problems = []
    who = f"{name} <{email}>".replace("`", "'")
    if AI_RE.search(name) or AI_RE.search(email):
        problems.append(f"{role} is an AI tool: {who}")
    elif email.lower() not in ALLOWED_BOTS and email.lower() not in extra_ok and not domain_ok(email):
        problems.append(f"{role} email is not {DOMAINS_TEXT}: {who}")
    return problems


def git(*args):
    return subprocess.run(["git", *args], check=True, capture_output=True, text=True).stdout


def check_commits(rev_range):
    results = []
    for sha in git("rev-list", "--reverse", rev_range).split():
        an, ae, cn, ce, body = git("show", "-s", "--format=%an%x00%ae%x00%cn%x00%ce%x00%B", sha).split("\0", 4)
        problems = check_identity("Author", an, ae)
        problems += check_identity("Committer", cn, ce, extra_ok={GITHUB_WEB_FLOW})
        problems += check_message(body, bot=ae.lower() in ALLOWED_BOTS)
        if problems:
            subject = body.splitlines()[0].replace("`", "'") if body.strip() else "(no message)"
            results.append((f"{sha[:12]} {subject}", problems))
    return results


def escape_annotation(text):
    return text.replace("%", "%25").replace("\r", "%0D").replace("\n", "%0A")


def write_report(path, results, base_ref):
    lines = [
        "### :no_entry: Commit attribution check failed",
        "",
        f"Every author, committer and `*-by:` line must be a real person with a {DOMAINS_TEXT} email.",
        "AI tools and toolchains (Claude, Copilot, ChatGPT, and so on) must not appear in commit messages.",
        "",
    ]
    identity_bad = message_bad = pr_bad = False
    for where, problems in results:
        lines.append(f"**{where}**")
        lines += [f"- {p}" for p in problems]
        lines.append("")
        if where == PR_TEXT_LABEL:
            pr_bad = True
            continue
        for p in problems:
            if p.startswith(("Author", "Committer")):
                identity_bad = True
            else:
                message_bad = True

    lines += ["#### How to fix", ""]
    if identity_bad or message_bad:
        lines += [
            "Rewrite the commits on your machine, then force-push. "
            "A new commit on top does **not** fix this, because the bad commit stays in history.",
            "",
            "```sh",
            "# 1. Get the PR branch (also for PRs made on GitHub, for example by an agent):",
            "git fetch origin",
            "git switch <pr-branch>",
            "",
            "# 2. Set your identity (once per machine):",
            'git config user.name  "Your Name"',
            f"git config user.email you{DOMAINS_TEXT}",
            "```",
            "",
        ]
    if message_bad:
        lines += [
            "Remove or correct the listed lines in each commit message:",
            "",
            "```sh",
            "# Last commit only:",
            "git commit --amend",
            "# Older commits: change 'pick' to 'reword' on each listed commit",
            f"git rebase -i origin/{base_ref}",
            "```",
            "",
        ]
    if identity_bad:
        lines += [
            "Make yourself the author and committer of every commit in the PR:",
            "",
            "```sh",
            f"git rebase origin/{base_ref} --exec 'git commit --amend --no-edit --reset-author'",
            "```",
            "",
        ]
    if identity_bad or message_bad:
        lines += [
            "Check locally, then update the PR:",
            "",
            "```sh",
            f"python3 .github/scripts/check_commit_attribution.py --range origin/{base_ref}..HEAD",
            "git push --force-with-lease",
            "```",
            "",
        ]
    if pr_bad:
        lines += ["Edit the PR title or description on GitHub. This check runs again after the edit.", ""]
    with open(path, "w", encoding="utf-8") as f:
        f.write("\n".join(lines) + "\n")


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--range", required=True, help="commit range, for example BASE..HEAD")
    p.add_argument("--base-ref", default="master")
    p.add_argument("--report", help="write a Markdown report here when problems are found")
    args = p.parse_args()

    try:
        results = check_commits(args.range)
    except subprocess.CalledProcessError as e:
        print(f"::error::git failed: {escape_annotation(e.stderr.strip())}")
        return 2

    pr_text = os.environ.get("PR_TITLE", "") + "\n" + os.environ.get("PR_BODY", "")
    pr_problems = check_message(pr_text)
    if pr_problems:
        results.append((PR_TEXT_LABEL, pr_problems))

    if not results:
        print("All commits have valid attribution.")
        return 0
    for where, problems in results:
        for prob in problems:
            print(f"::error title=Commit attribution::{escape_annotation(f'{where}: {prob}')}")
    if args.report:
        write_report(args.report, results, args.base_ref)
    return 1


if __name__ == "__main__":
    sys.exit(main())
