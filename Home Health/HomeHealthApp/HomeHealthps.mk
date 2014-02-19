
MDFMDIAppps.dll: dlldata.obj MDFMDIApp_p.obj MDFMDIApp_i.obj
	link /dll /out:MDFMDIAppps.dll /def:MDFMDIAppps.def /entry:DllMain dlldata.obj MDFMDIApp_p.obj MDFMDIApp_i.obj \
		kernel32.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
.c.obj:
	cl /c /Ox /DREGISTER_PROXY_DLL \
		$<

clean:
	@del MDFMDIAppps.dll
	@del MDFMDIAppps.lib
	@del MDFMDIAppps.exp
	@del dlldata.obj
	@del MDFMDIApp_p.obj
	@del MDFMDIApp_i.obj
