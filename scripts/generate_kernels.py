import os
import sys
import binascii

archs = ['skl', 'ats']
suffixes = ['_Gen9core', '_Gen12HPcore']
kernels = ['copyBufferToBufferBytes']
kernelsLoc = "../core/source/kernels/"

def create_kernels():
    for k in kernels:
        for a in archs:
            kernelCL = kernelsLoc + k + ".cl"

            kernelArchName = ""
            if a == 'skl':
                kernelArchName = k + "_Gen9core"
            if a == 'ats':
                kernelArchName = k + "_Gen12HPcore"

            kernelSPV = kernelsLoc + kernelArchName + ".spv"
            kernelTXT = kernelsLoc + kernelArchName + ".hpp"

            #Compile OpenCL kernel into SPIR-V
            try:
                os.path.isfile(kernelCL)
            except IOError:
                print("No OpenCL found\n");
                raise

            os.system("ocloc -device %s -file %s -out_dir %s" %(a, kernelCL, kernelsLoc))

            #Read SPIR-V file
            try:
                spirvFile = open(kernelSPV, 'rb')
            except IOError:
                print("No spirvFile found\n");
                raise
            else:
                if os.path.exists(kernelTXT):
                    os.remove(kernelTXT)
                try:
                    spirvTxtFile = open(kernelTXT, 'w', encoding="utf8", errors='ignore')
                except IOError:
                    print("Not able to create file\n");
                    raise
                else:

                    # Create an HPP file with the SPIR-V file's content
                    spirvTxtFile.write("#ifndef _%s_\n"% (kernelArchName));
                    spirvTxtFile.write("#define _%s_\n"% (kernelArchName));
                    spirvFileSize=os.fstat(spirvFile.fileno()).st_size

                    i = 0
                    spirvTxtFile.write("unsigned char spirv_%s [] = {" % (kernelArchName));
                    c = spirvFile.read(1)
                    while c:
                        s = "%x" % ord(c)

                        if i == 0:
                            spirvTxtFile.write("0x");
                        elif i < spirvFileSize - 1:
                            spirvTxtFile.write(",0x");

                        spirvTxtFile.write(s)

                        if i % 16 == 0:
                            spirvTxtFile.write("\n");

                        c = spirvFile.read(1)

                        i = i + 1

                    spirvTxtFile.write("};\n")
                    spirvTxtFile.write("uint32_t size_%s = %d;\n" % (kernelArchName, spirvFileSize));
                    spirvTxtFile.write("#endif\n");

                    spirvTxtFile.close()
                    spirvFile.close()

def main():
    create_kernels()

if __name__ == '__main__':
    main()