<%!
import re
import extended_helper as th
%>LIBRARY    "<%text>$</%text>{MSVC_DEF_LIB_NAME}"
EXPORTS
%for obj in objects:
%for cli, cls in enumerate(obj['class']):
%if re.match(r"function", obj['type']):
${th.make_func_name(x, obj, cls)}
%endif
%endfor
%endfor
