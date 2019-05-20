import os
import sys
import binascii
import re

copyKernelFiles = ['copy_buffer_to_buffer_bytes', 'copy_buffer_to_buffer_decomposed']
kernelsLoc = "../source/core/kernels/"

def create_kernels():
    for kernelFileName in copyKernelFiles:
            kernelCL = kernelsLoc + kernelFileName + ".cl"
            kernelSPV = kernelsLoc + kernelFileName + "_Gen12HPcore.spv"
            kernelBIN = kernelsLoc + kernelFileName + "_Gen12HPcore.bin"
            kernelGEN = kernelsLoc + kernelFileName + "_Gen12HPcore.gen"
            kernelTXT = kernelsLoc + kernelFileName + ".h"

            #Compile OpenCL kernel into SPIR-V
            try:
                os.path.isfile(kernelCL)
            except IOError:
                print("No OpenCL found\n");
                raise

            os.system("ocloc -device ats -file %s -out_dir %s" %(kernelCL, kernelsLoc))
            if os.path.exists(kernelBIN):
                    os.remove(kernelBIN)
            if os.path.exists(kernelGEN):
                    os.remove(kernelGEN)

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
                    spirvTxtFile.write("// Auto-generated header; see scripts/generate_kernels.py\n");
                    spirvTxtFile.write("#pragma once\n\n");
                    spirvFileSize=os.fstat(spirvFile.fileno()).st_size

                    i = 0
                    spirvTxtFile.write("static const unsigned char spirv_%s[] = {" % (kernelFileName));
                    c = spirvFile.read(1)
                    while c:
                        s = "%x" % ord(c)

                        if i == 0:
                            spirvTxtFile.write("0x");
                        else:
                            spirvTxtFile.write(", 0x");

                        spirvTxtFile.write(s)

                        c = spirvFile.read(1)

                        i = i + 1

                    spirvTxtFile.write("};\n")
                    spirvTxtFile.close()
                    spirvFile.close()

                    os.remove(kernelSPV)

def main():
    create_kernels()

if __name__ == '__main__':
    main()
