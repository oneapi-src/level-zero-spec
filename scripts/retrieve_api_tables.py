"""
 Copyright (C) 2025 Intel Corporation

 SPDX-License-Identifier: MIT

"""
import os
import yaml
import csv
import argparse

def extract_apis_by_version(directory):
    api_data = []

    # Walk through the directory and its subdirectories
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".yml"):
                file_path = os.path.join(root, file)
                with open(file_path, 'r') as f:
                    try:
                        # Load YAML content
                        docs = list(yaml.safe_load_all(f))
                        for doc in docs:
                            # Extract API name, version, and symbol type if available
                            if isinstance(doc, dict) and 'name' in doc:
                                name = doc.get('name')
                                version = doc.get('version', '1.0 - default')  # Default to '1.0' if version is missing
                                symbol_class = doc.get('class', 'unknown')  # Default to 'unknown' if type is missing
                                type = doc.get('type')
                                # Determine namespace based on the top-level folder
                                top_level_folder = os.path.basename(os.path.dirname(file_path))
                                namespace_map = {
                                    'core': 'ze',
                                    'tools': 'zet',
                                    'sysman': 'zes'
                                }
                                namespace = namespace_map.get(top_level_folder, '')  # Default to empty if not matched
                                # Replace $t in the name with the namespace
                                if '$t' in name:
                                    name = name.replace('$t', namespace)
                                # Replace $T in the name with the namespace
                                if '$T' in name:
                                    name = name.replace('$T', namespace)
                                if '$s' in name:
                                    name = name.replace('$s', namespace)
                                # Replace $S in the name with the namespace
                                if '$S' in name:
                                    name = name.replace('$S', namespace)
                                if '$x' in name:
                                    name = name.replace('$x', namespace)
                                # Replace $X in the name with the namespace
                                if '$X' in name:
                                    name = name.replace('$X', namespace)
                                # Replace $x in the name with empty
                                if ('$x' in symbol_class or '$t' in symbol_class or '$s' in symbol_class) and type == 'function':
                                    symbol_class = symbol_class.replace('$x', '')
                                    symbol_class = symbol_class.replace('$s', '')
                                    symbol_class = symbol_class.replace('$t', '')
                                    full_name = f"{namespace}{symbol_class}{name}"
                                else:
                                    full_name = f"{name}"
                                api_data.append((full_name, version, type, file_path))
                    except yaml.YAMLError as e:
                        print(f"Error parsing {file_path}: {e}")

    return api_data

def write_to_csv(api_data, output_file):
    # Write the extracted data to a CSV file
    with open(output_file, 'w', newline='') as csvfile:
        csv_writer = csv.writer(csvfile)
        # Write header
        csv_writer.writerow(['Symbol Name', 'Version', 'Type', 'File Path'])
        # Write rows
        csv_writer.writerows(api_data)

if __name__ == "__main__":
    # Define the directory to search and the output CSV file
    # Parse command-line arguments
    parser = argparse.ArgumentParser(description="Extract API versions from YAML files.")
    parser.add_argument("scripts_directory", help="Path to the directory containing the scripts")
    args = parser.parse_args()

    scripts_directory = args.scripts_directory
    output_csv = "api_versions.csv"

    # Extract API data and write to CSV
    api_data = extract_apis_by_version(scripts_directory)
    write_to_csv(api_data, output_csv)

    print(f"API version data has been written to {output_csv}")
