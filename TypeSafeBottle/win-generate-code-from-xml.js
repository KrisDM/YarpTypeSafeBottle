var args = WScript.Arguments;
var outfile = args(0);
var xmlfile = args(1);
var xslfile = args(2);
var xmldoc = new ActiveXObject(\"MSXML2.DOMDocument.6.0\");
var xsldoc = new ActiveXObject(\"MSXML2.DOMDOCUMENT.6.0\");
xmldoc.async = false;
xmldoc.validateOnParse = false;
xmldoc.load(xmlfile);
if (xmldoc.parseError.errorCode != 0)
	WScript.Echo (\"XML Parse Error : \" + xmldoc.parseError.reason);

xsldoc.async = false;
xsldoc.resolveExternals = true;
xsldoc.load(xslfile);
if (xsldoc.parseError.errorCode != 0)
	WScript.Echo (\"XML Parse Error : \" + xsldoc.parseError.reason);

/* Create a binary IStream */
var outdoc = new ActiveXObject(\"ADODB.Stream\");
outdoc.type = 1;
outdoc.open();
xmldoc.transformNodeToObject(xsldoc,outdoc);
outdoc.SaveToFile(outfile,2);