# invoke SourceDir generated makefile for enc_rtos.pem4f
enc_rtos.pem4f: .libraries,enc_rtos.pem4f
.libraries,enc_rtos.pem4f: package/cfg/enc_rtos_pem4f.xdl
	$(MAKE) -f C:\Users\Julio\workspace_v8\Quad_Encoder/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\Julio\workspace_v8\Quad_Encoder/src/makefile.libs clean

