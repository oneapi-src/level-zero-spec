#include "xello_worlds.h"

#include "xe_all.h"

#include <iostream>
#include <fstream>
#include <memory>

extern bool verbose;
bool verbose = false;

const char *llvmCodeGlobalVariables = R"===(
; ------------------------------------------------
; Global variables pointers POC
; ------------------------------------------------
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-f80:128:128-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-f80:128:128-n8:16:32"
target triple = "unknown64-unknown-unknown"

@b = common addrspace(1) global [100 x i32] zeroinitializer, align 4
@c = common addrspace(1) global [4 x i32] [i32 2, i32 3, i32 5, i32 7], align 4
@d = common addrspace(2) constant [4 x i32] [i32 11, i32 13, i32 17, i32 19], align 4
@a = common addrspace(1) global [100 x i32] zeroinitializer, align 4
)===";

const char *llvmCodeFuncArray = R"===(
; ------------------------------------------------
; Functions pointers POC
; ------------------------------------------------
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-f80:128:128-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-f80:128:128-n8:16:32"
target triple = "unknown64-unknown-unknown"

; Function Attrs: nounwind
define i32 @mul(i32 %a, i32 %b) #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 %a, i32* %1, align 4
  store i32 %b, i32* %2, align 4
  %3 = load i32, i32* %1, align 4
  %4 = load i32, i32* %2, align 4
  %5 = mul i32 %3, %4
  ret i32 %5
}

; Function Attrs: nounwind
define i32 @add(i32 %a, i32 %b) #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 %a, i32* %1, align 4
  store i32 %b, i32* %2, align 4
  %3 = load i32, i32* %1, align 4
  %4 = load i32, i32* %2, align 4
  %5 = add i32 %3, %4
  ret i32 %5
}

; Function Attrs: nounwind
define i32 @sub(i32 %a, i32 %b) #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 %a, i32* %1, align 4
  store i32 %b, i32* %2, align 4
  %3 = load i32, i32* %1, align 4
  %4 = load i32, i32* %2, align 4
  %5 = sub i32 %3, %4
  ret i32 %5
}

; Function Attrs: nounwind
define void @fptr_array(i32 addrspace(1)* %dst, i32 %a, i32 %b, i32 %comp) #0 {
  %gidXYZ = call spir_func <3 x i64> @__builtin_spirv_BuiltInGlobalInvocationId() #1
  %gidX = extractelement <3 x i64> %gidXYZ, i32 0
  %dstIt = getelementptr inbounds i32, i32 addrspace(1)* %dst, i64 %gidX

  %funptr = alloca [3 x i32 (i32, i32)*], align 16
  %fun1 = getelementptr inbounds [3 x i32 (i32, i32)*], [3 x i32 (i32, i32)*]* %funptr, i64 0, i64 0
  store i32 (i32, i32)* @add, i32 (i32, i32)** %fun1, align 4
  %fun2 = getelementptr inbounds [3 x i32 (i32, i32)*], [3 x i32 (i32, i32)*]* %funptr, i64 0, i64 1
  store i32 (i32, i32)* @sub, i32 (i32, i32)** %fun2, align 4
  %fun3 = getelementptr inbounds [3 x i32 (i32, i32)*], [3 x i32 (i32, i32)*]* %funptr, i64 0, i64 2
  store i32 (i32, i32)* @mul, i32 (i32, i32)** %fun3, align 4
  %index = zext i32 %comp to i64
  %func_p = getelementptr inbounds [3 x i32 (i32, i32)*], [3 x i32 (i32, i32)*]* %funptr, i64 0, i64 %index
  %fcall = load i32 (i32, i32)*, i32 (i32, i32)** %func_p, align 4
  %result = call i32 %fcall(i32 %a, i32 %b)
  store i32 %result, i32 addrspace(1)* %dstIt, align 4
  ret void
}

; Function Attrs: nounwind readnone
declare spir_func <3 x i64> @__builtin_spirv_BuiltInGlobalInvocationId() #1

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-realign-stack" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind }

!opencl.kernels = !{!0}
!igc.input.ir = !{}
!igc.functions = !{}
!IGCMetadata = !{!5}

!0 = !{void (i32 addrspace(1)*, i32, i32, i32)* @fptr_array}
!5 = !{!"ModuleMD", !6, !7, !29, !30, !50, !52, !65, !71, !79, !81, !82, !83, !85, !86, !87, !88, !89, !90, !91, !93, !97, !98, !99}
!6 = !{!"isPrecise", i1 false}
!7 = !{!"compOpt", !8, !9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28}
!8 = !{!"DenormsAreZero", i1 false}
!9 = !{!"CorrectlyRoundedDivSqrt", i1 false}
!10 = !{!"OptDisable", i1 false}
!11 = !{!"MadEnable", i1 false}
!12 = !{!"NoSignedZeros", i1 false}
!13 = !{!"FloatRoundingMode", i32 0}
!14 = !{!"UnsafeMathOptimizations", i1 false}
!15 = !{!"FiniteMathOnly", i1 false}
!16 = !{!"FastRelaxedMath", i1 false}
!17 = !{!"DashGSpecified", i1 false}
!18 = !{!"FastCompilation", i1 false}
!19 = !{!"UseScratchSpacePrivateMemory", i1 true}
!20 = !{!"RelaxedBuiltins", i1 false}
!21 = !{!"SubgroupIndependentForwardProgressRequired", i1 true}
!22 = !{!"GreaterThan2GBBufferRequired", i1 true}
!23 = !{!"GreaterThan4GBBufferRequired", i1 true}
!24 = !{!"PushConstantsEnable", i1 true}
!25 = !{!"HasBufferOffsetArg", i1 false}
!26 = !{!"replaceGlobalOffsetsByZero", i1 false}
!27 = !{!"forcePixelShaderSIMDMode", i32 0}
!28 = !{!"pixelShaderDoNotAbortOnSpill", i1 false}
!29 = !{!"FuncMD"}
!30 = !{!"pushInfo", !31, !32, !33, !34, !35, !36, !37, !38, !48, !49}
!31 = !{!"pushableAddresses"}
!32 = !{!"MaxNumberOfPushedBuffers", i32 0}
!33 = !{!"inlineConstantBufferSlot", i32 -1}
!34 = !{!"inlineConstantBufferOffset", i32 -1}
!35 = !{!"constants"}
!36 = !{!"inputs"}
!37 = !{!"constantReg"}
!38 = !{!"simplePushInfoArr", !39, !45, !46, !47}
!39 = !{!"simplePushInfoArrVec[0]", !40, !41, !42, !43, !44}
!40 = !{!"cbIdx", i32 0}
!41 = !{!"offset", i32 0}
!42 = !{!"size", i32 0}
!43 = !{!"isStateless", i1 false}
!44 = !{!"simplePushLoads"}
!45 = !{!"simplePushInfoArrVec[1]", !40, !41, !42, !43, !44}
!46 = !{!"simplePushInfoArrVec[2]", !40, !41, !42, !43, !44}
!47 = !{!"simplePushInfoArrVec[3]", !40, !41, !42, !43, !44}
!48 = !{!"simplePushBufferUsed", i32 0}
!49 = !{!"pushAnalysisWIInfos"}
!50 = !{!"vsInfo", !51}
!51 = !{!"DrawIndirectBufferIndex", i32 -1}
!52 = !{!"psInfo", !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64}
!53 = !{!"BlendStateDisabledMask", i8 0}
!54 = !{!"SkipSrc0Alpha", i1 false}
!55 = !{!"DualSourceBlendingDisabled", i1 false}
!56 = !{!"ForceEnableSimd32", i1 false}
!57 = !{!"outputDepth", i1 false}
!58 = !{!"outputStencil", i1 false}
!59 = !{!"outputMask", i1 false}
!60 = !{!"blendToFillEnabled", i1 false}
!61 = !{!"forceEarlyZ", i1 false}
!62 = !{!"hasVersionedLoop", i1 false}
!63 = !{!"blendOptimizationMode"}
!64 = !{!"colorOutputMask"}
!65 = !{!"csInfo", !66, !67, !68, !69, !70}
!66 = !{!"maxWorkGroupSize", i32 0}
!67 = !{!"waveSize", i32 0}
!68 = !{!"ComputeShaderSecondCompile"}
!69 = !{!"forcedSIMDSize", i8 0}
!70 = !{!"forcedVISAPreRAScheduler", i1 false}
!71 = !{!"msInfo", !72, !73, !74, !75, !76, !77, !78}
!72 = !{!"PrimitiveTopology", i32 3}
!73 = !{!"MaxNumOfPrimitives", i32 0}
!74 = !{!"MaxNumOfVertices", i32 0}
!75 = !{!"MaxNumOfPerPrimitiveOutputs", i32 0}
!76 = !{!"MaxNumOfPerVertexOutputs", i32 0}
!77 = !{!"WorkGroupSize", i32 0}
!78 = !{!"IndexFormat", i32 4}
!79 = !{!"taskInfo", !80, !77}
!80 = !{!"MaxNumOfOutputs", i32 0}
!81 = !{!"inlineDynConstants"}
!82 = !{!"inlineDynTextures"}
!83 = !{!"immConstant", !84}
!84 = !{!"data"}
!85 = !{!"inlineConstantBuffers"}
!86 = !{!"inlineGlobalBuffers"}
!87 = !{!"GlobalPointerProgramBinaryInfos"}
!88 = !{!"ConstantPointerProgramBinaryInfos"}
!89 = !{!"MinNOSPushConstantSize", i32 0}
!90 = !{!"inlineProgramScopeOffsets"}
!91 = !{!"shaderData", !92}
!92 = !{!"numReplicas", i32 0}
!93 = !{!"URBInfo", !94, !95, !96}
!94 = !{!"has64BVertexHeaderInput", i1 false}
!95 = !{!"has64BVertexHeaderOutput", i1 false}
!96 = !{!"hasVertexHeader", i1 true}
!97 = !{!"UseBindlessImage", i1 false}
!98 = !{!"statefullResourcesNotAliased", i1 false}
!99 = !{!"privateMemoryPerWI", i32 0}

)===";

#if 0
const char *llvmCodeFuncParam = R"===(
; ------------------------------------------------
; Functions pointers as params POC
; ------------------------------------------------
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-f80:128:128-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-f80:128:128-n8:16:32"
target triple = "unknown64-unknown-unknown"

; Function Attrs: nounwind
define void @fptr_param(i32 addrspace(1)* %dst, i32 %a, i32 %b, i32* %op_opaque) #0 {
  %gidXYZ = call spir_func <3 x i64> @__builtin_spirv_BuiltInGlobalInvocationId() #1
  %gidX = extractelement <3 x i64> %gidXYZ, i32 0
  %dstIt = getelementptr inbounds i32, i32 addrspace(1)* %dst, i64 %gidX

  %op = bitcast i32* %op_opaque to i32 (i32, i32)*

  %result = call i32 %op(i32 %a, i32 %b)
  store i32 %result, i32 addrspace(1)* %dstIt, align 4
  ret void
}

; Function Attrs: nounwind readnone
declare spir_func <3 x i64> @__builtin_spirv_BuiltInGlobalInvocationId() #1

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-realign-stack" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind }

!opencl.kernels = !{!0}
!igc.input.ir = !{}
!igc.functions = !{}
!IGCMetadata = !{!5}

!0 = !{void (i32 addrspace(1)*, i32, i32, i32* )* @fptr_param}
!5 = !{!"ModuleMD", !6, !7, !29, !30, !50, !52, !65, !71, !79, !81, !82, !83, !85, !86, !87, !88, !89, !90, !91, !93, !97, !98, !99}
!6 = !{!"isPrecise", i1 false}
!7 = !{!"compOpt", !8, !9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28}
!8 = !{!"DenormsAreZero", i1 false}
!9 = !{!"CorrectlyRoundedDivSqrt", i1 false}
!10 = !{!"OptDisable", i1 false}
!11 = !{!"MadEnable", i1 false}
!12 = !{!"NoSignedZeros", i1 false}
!13 = !{!"FloatRoundingMode", i32 0}
!14 = !{!"UnsafeMathOptimizations", i1 false}
!15 = !{!"FiniteMathOnly", i1 false}
!16 = !{!"FastRelaxedMath", i1 false}
!17 = !{!"DashGSpecified", i1 false}
!18 = !{!"FastCompilation", i1 false}
!19 = !{!"UseScratchSpacePrivateMemory", i1 true}
!20 = !{!"RelaxedBuiltins", i1 false}
!21 = !{!"SubgroupIndependentForwardProgressRequired", i1 true}
!22 = !{!"GreaterThan2GBBufferRequired", i1 true}
!23 = !{!"GreaterThan4GBBufferRequired", i1 true}
!24 = !{!"PushConstantsEnable", i1 true}
!25 = !{!"HasBufferOffsetArg", i1 false}
!26 = !{!"replaceGlobalOffsetsByZero", i1 false}
!27 = !{!"forcePixelShaderSIMDMode", i32 0}
!28 = !{!"pixelShaderDoNotAbortOnSpill", i1 false}
!29 = !{!"FuncMD"}
!30 = !{!"pushInfo", !31, !32, !33, !34, !35, !36, !37, !38, !48, !49}
!31 = !{!"pushableAddresses"}
!32 = !{!"MaxNumberOfPushedBuffers", i32 0}
!33 = !{!"inlineConstantBufferSlot", i32 -1}
!34 = !{!"inlineConstantBufferOffset", i32 -1}
!35 = !{!"constants"}
!36 = !{!"inputs"}
!37 = !{!"constantReg"}
!38 = !{!"simplePushInfoArr", !39, !45, !46, !47}
!39 = !{!"simplePushInfoArrVec[0]", !40, !41, !42, !43, !44}
!40 = !{!"cbIdx", i32 0}
!41 = !{!"offset", i32 0}
!42 = !{!"size", i32 0}
!43 = !{!"isStateless", i1 false}
!44 = !{!"simplePushLoads"}
!45 = !{!"simplePushInfoArrVec[1]", !40, !41, !42, !43, !44}
!46 = !{!"simplePushInfoArrVec[2]", !40, !41, !42, !43, !44}
!47 = !{!"simplePushInfoArrVec[3]", !40, !41, !42, !43, !44}
!48 = !{!"simplePushBufferUsed", i32 0}
!49 = !{!"pushAnalysisWIInfos"}
!50 = !{!"vsInfo", !51}
!51 = !{!"DrawIndirectBufferIndex", i32 -1}
!52 = !{!"psInfo", !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64}
!53 = !{!"BlendStateDisabledMask", i8 0}
!54 = !{!"SkipSrc0Alpha", i1 false}
!55 = !{!"DualSourceBlendingDisabled", i1 false}
!56 = !{!"ForceEnableSimd32", i1 false}
!57 = !{!"outputDepth", i1 false}
!58 = !{!"outputStencil", i1 false}
!59 = !{!"outputMask", i1 false}
!60 = !{!"blendToFillEnabled", i1 false}
!61 = !{!"forceEarlyZ", i1 false}
!62 = !{!"hasVersionedLoop", i1 false}
!63 = !{!"blendOptimizationMode"}
!64 = !{!"colorOutputMask"}
!65 = !{!"csInfo", !66, !67, !68, !69, !70}
!66 = !{!"maxWorkGroupSize", i32 0}
!67 = !{!"waveSize", i32 0}
!68 = !{!"ComputeShaderSecondCompile"}
!69 = !{!"forcedSIMDSize", i8 0}
!70 = !{!"forcedVISAPreRAScheduler", i1 false}
!71 = !{!"msInfo", !72, !73, !74, !75, !76, !77, !78}
!72 = !{!"PrimitiveTopology", i32 3}
!73 = !{!"MaxNumOfPrimitives", i32 0}
!74 = !{!"MaxNumOfVertices", i32 0}
!75 = !{!"MaxNumOfPerPrimitiveOutputs", i32 0}
!76 = !{!"MaxNumOfPerVertexOutputs", i32 0}
!77 = !{!"WorkGroupSize", i32 0}
!78 = !{!"IndexFormat", i32 4}
!79 = !{!"taskInfo", !80, !77}
!80 = !{!"MaxNumOfOutputs", i32 0}
!81 = !{!"inlineDynConstants"}
!82 = !{!"inlineDynTextures"}
!83 = !{!"immConstant", !84}
!84 = !{!"data"}
!85 = !{!"inlineConstantBuffers"}
!86 = !{!"inlineGlobalBuffers"}
!87 = !{!"GlobalPointerProgramBinaryInfos"}
!88 = !{!"ConstantPointerProgramBinaryInfos"}
!89 = !{!"MinNOSPushConstantSize", i32 0}
!90 = !{!"inlineProgramScopeOffsets"}
!91 = !{!"shaderData", !92}
!92 = !{!"numReplicas", i32 0}
!93 = !{!"URBInfo", !94, !95, !96}
!94 = !{!"has64BVertexHeaderInput", i1 false}
!95 = !{!"has64BVertexHeaderOutput", i1 false}
!96 = !{!"hasVertexHeader", i1 true}
!97 = !{!"UseBindlessImage", i1 false}
!98 = !{!"statefullResourcesNotAliased", i1 false}
!99 = !{!"privateMemoryPerWI", i32 0}

)===";
#endif

// Disable GPU_COPY so that GPU processes only required
#define GPU_COPY

void initializeLevelZero(xe_device_handle_t &device0, xe_device_properties_t &device0Properties,
                         xe_command_queue_handle_t &cmdQueue, xe_command_list_handle_t &cmdList, xe_mem_allocator_handle_t &allocator,
                         xe_module_handle_t &moduleGlobalVariables,
                         xe_module_handle_t &moduleFuncArray, xe_function_handle_t &functionFuncArray,
                         xe_module_handle_t &moduleFuncParam, xe_function_handle_t &functionFuncParam);

int main(int argc, char *argv[]) {
    if (isAubMode(argc, argv)) {
        return 0; // disable from automatic execution till proper IGC changes are pulled-in
    }
    verbose = isVerbose(argc, argv);
    // 0. Load the driver
    // Using icd loader linked statically into this executable
    xe_device_handle_t device0;
    xe_device_properties_t device0Properties;
    xe_module_handle_t moduleGlobalVariables;
    xe_module_handle_t moduleFuncArray;
    xe_function_handle_t functionFuncArray;
    xe_module_handle_t moduleFuncParam;
    xe_function_handle_t functionFuncParam;
    xe_command_queue_handle_t cmdQueue;
    xe_command_list_handle_t cmdList;
    xe_mem_allocator_handle_t allocator;
    initializeLevelZero(device0, device0Properties, cmdQueue, cmdList, allocator,
                        moduleGlobalVariables,
                        moduleFuncArray, functionFuncArray,
                        moduleFuncParam, functionFuncParam);

    // 1. Set-up
    using ElType = int32_t;
    constexpr size_t elCount = 64;
    constexpr size_t allocSize = elCount * sizeof(ElType);

    constexpr size_t numSimtThreads = elCount;

    void *dstBufferOpAdd = nullptr;
    void *dstBufferOpSub = nullptr;
    void *dstBufferOpMul = nullptr;

    constexpr int operandA = 19;
    constexpr int operandB = 17;
    constexpr int opCodeAdd = 0;
    constexpr int opCodeSub = 1;
    constexpr int opCodeMul = 2;

    uint32_t groupSizeX = 32u, groupSizeY = 1u, groupSizeZ = 1u;
    SUCCESS_OR_TERMINATE(xeFunctionSuggestGroupSize(functionFuncArray, numSimtThreads, 1U, 1U, &groupSizeX, &groupSizeY, &groupSizeZ));
    SUCCESS_OR_TERMINATE_BOOL(numSimtThreads % groupSizeX == 0);
    if (verbose) {
        std::cout << "Group size : (" << groupSizeX << ", " << groupSizeY << ", " << groupSizeZ << ")" << std::endl;
    }
    SUCCESS_OR_TERMINATE(xeFunctionSetGroupSize(functionFuncArray, groupSizeX, groupSizeY, groupSizeZ));

    SUCCESS_OR_TERMINATE(xeSharedMemAlloc(allocator, device0, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, XE_HOST_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &dstBufferOpAdd));
    SUCCESS_OR_TERMINATE(xeSharedMemAlloc(allocator, device0, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, XE_HOST_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &dstBufferOpMul));
    SUCCESS_OR_TERMINATE(xeSharedMemAlloc(allocator, device0, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT, XE_HOST_MEM_ALLOC_FLAG_DEFAULT, allocSize, 1, &dstBufferOpSub));

    void *fptrSub = nullptr;
    void *fptrAdd = nullptr;
    void *fptrMul = nullptr;
    SUCCESS_OR_TERMINATE(xeModuleGetFunctionPointer(moduleFuncArray, "sub", &fptrSub));
    SUCCESS_OR_TERMINATE(xeModuleGetFunctionPointer(moduleFuncArray, "add", &fptrAdd));
    SUCCESS_OR_TERMINATE(xeModuleGetFunctionPointer(moduleFuncArray, "mul", &fptrMul));

    void *gptrA = nullptr;
    void *gptrB = nullptr;
    void *gptrC = nullptr;
    void *gptrD = nullptr;
    SUCCESS_OR_TERMINATE(xeModuleGetGlobalPointer(moduleGlobalVariables, "a", &gptrA));
    SUCCESS_OR_TERMINATE(xeModuleGetGlobalPointer(moduleGlobalVariables, "b", &gptrB));
    SUCCESS_OR_TERMINATE(xeModuleGetGlobalPointer(moduleGlobalVariables, "c", &gptrC));
    SUCCESS_OR_TERMINATE(xeModuleGetGlobalPointer(moduleGlobalVariables, "d", &gptrD));

    // 2. Initialize memory
    uint8_t initDataDst[allocSize];
    memset(initDataDst, 0xFF, sizeof(initDataDst));

#ifdef GPU_COPY
    SUCCESS_OR_TERMINATE(xeCommandListAppendMemoryCopy(cmdList, dstBufferOpAdd, initDataDst, sizeof(initDataDst)));
    SUCCESS_OR_TERMINATE(xeCommandListAppendMemoryCopy(cmdList, dstBufferOpMul, initDataDst, sizeof(initDataDst)));
    SUCCESS_OR_TERMINATE(xeCommandListAppendMemoryCopy(cmdList, dstBufferOpSub, initDataDst, sizeof(initDataDst)));

    SUCCESS_OR_TERMINATE(xeCommandListAppendExecutionBarrier(cmdList)); // copying of data must finish before running the user function
#else
    memcpy(dstBufferOpAdd, initDataDst, sizeof(initDataDst));
    memcpy(dstBufferOpMul, initDataDst, sizeof(initDataDst));
    memcpy(dstBufferOpSub, initDataDst, sizeof(initDataDst));
#endif

    // 3. User function
    SUCCESS_OR_TERMINATE(xeFunctionSetArgumentValue(functionFuncArray, 0, sizeof(dstBufferOpAdd), &dstBufferOpAdd));
    SUCCESS_OR_TERMINATE(xeFunctionSetArgumentValue(functionFuncArray, 1, sizeof(operandA), &operandA));
    SUCCESS_OR_TERMINATE(xeFunctionSetArgumentValue(functionFuncArray, 2, sizeof(operandB), &operandB));
    //SUCCESS_OR_TERMINATE(xeFunctionSetArgumentValue(function, 3, sizeof(opCodeMul), &opCodeMul));
    SUCCESS_OR_TERMINATE(xeFunctionSetArgumentValue(functionFuncArray, 3, sizeof(opCodeAdd), &opCodeAdd));
    {
        xe_thread_group_dimensions_t dispatchTraits;
        dispatchTraits.groupCountX = numSimtThreads / groupSizeX;
        dispatchTraits.groupCountY = 1u;
        dispatchTraits.groupCountZ = 1u;
        if (verbose) {
            std::cerr << "Number of groups : (" << dispatchTraits.groupCountX << ", " << dispatchTraits.groupCountY << ", " << dispatchTraits.groupCountZ << ")" << std::endl;
        }
        SUCCESS_OR_TERMINATE_BOOL(dispatchTraits.groupCountX * groupSizeX == numSimtThreads);
        SUCCESS_OR_TERMINATE(xeCommandListAppendLaunchFunction(cmdList, functionFuncArray, &dispatchTraits, nullptr));
    }

    // 4. Read back memory
    ElType readBackDataOpAdd[elCount];
    ElType readBackDataOpSub[elCount];
    ElType readBackDataOpMul[elCount];
    memset(readBackDataOpAdd, 0xFF, sizeof(readBackDataOpAdd));
    memset(readBackDataOpSub, 0xFF, sizeof(readBackDataOpSub));
    memset(readBackDataOpMul, 0xFF, sizeof(readBackDataOpMul));

#ifdef GPU_COPY
    SUCCESS_OR_TERMINATE(xeCommandListAppendExecutionBarrier(cmdList)); // user function must finish before we start copying data
    SUCCESS_OR_TERMINATE(xeCommandListAppendMemoryCopy(cmdList, readBackDataOpAdd, dstBufferOpAdd, sizeof(readBackDataOpAdd)));
    SUCCESS_OR_TERMINATE(xeCommandListAppendMemoryCopy(cmdList, readBackDataOpSub, dstBufferOpSub, sizeof(readBackDataOpSub)));
    SUCCESS_OR_TERMINATE(xeCommandListAppendMemoryCopy(cmdList, readBackDataOpMul, dstBufferOpMul, sizeof(readBackDataOpMul)));
#endif

    // 5. Execute and wait
    SUCCESS_OR_TERMINATE(xeCommandListClose(cmdList));
    SUCCESS_OR_TERMINATE(xeCommandQueueExecuteCommandLists(cmdQueue, 1, &cmdList, nullptr));
    SUCCESS_OR_TERMINATE(xeCommandQueueSynchronize(cmdQueue, std::numeric_limits<uint32_t>::max()));

#ifdef GPU_COPY
#else
    memcpy(readBackDataOpAdd, dstBufferOpAdd, sizeof(readBackDataOpAdd));
    memcpy(readBackDataOpSub, dstBufferOpSub, sizeof(readBackDataOpSub));
    memcpy(readBackDataOpMul, dstBufferOpMul, sizeof(readBackDataOpMul));
#endif

    // 6. Validate
    std::vector<ElType> expectedData;
    expectedData.clear();
    expectedData.resize(elCount, operandA + operandB);
    bool outputValidationSuccessful = validate<int>(expectedData.data(), readBackDataOpAdd, elCount);
    SUCCESS_OR_WARNING_BOOL(outputValidationSuccessful);

    // X. Cleanup
    SUCCESS_OR_TERMINATE(xeMemFree(allocator, dstBufferOpAdd));
    SUCCESS_OR_TERMINATE(xeMemFree(allocator, dstBufferOpSub));
    SUCCESS_OR_TERMINATE(xeMemFree(allocator, dstBufferOpMul));
    SUCCESS_OR_TERMINATE(xeMemAllocatorDestroy(allocator));

    SUCCESS_OR_TERMINATE(xeCommandListDestroy(cmdList));

    SUCCESS_OR_TERMINATE(xeCommandQueueDestroy(cmdQueue));

    SUCCESS_OR_TERMINATE(xeFunctionDestroy(functionFuncArray));
    SUCCESS_OR_TERMINATE(xeModuleDestroy(moduleFuncArray));

    bool aubMode = isAubMode(argc, argv);
    if (aubMode == false) {
        std::cout << "\nResults validation " << (outputValidationSuccessful ? "PASSED" : "FAILED") << std::endl;
    }
    int resultOnFailure = aubMode ? 0 : 1;
    return outputValidationSuccessful ? 0 : resultOnFailure;
}

void initializeLevelZero(xe_device_handle_t &device0, xe_device_properties_t &device0Properties,
                         xe_command_queue_handle_t &cmdQueue, xe_command_list_handle_t &cmdList, xe_mem_allocator_handle_t &allocator,
                         xe_module_handle_t &moduleGlobalVariables,
                         xe_module_handle_t &moduleFuncArray, xe_function_handle_t &functionFuncArray,
                         xe_module_handle_t &moduleFuncParam, xe_function_handle_t &functionFuncParam) {
    device0 = {};
    device0Properties = {XE_DEVICE_PROPERTIES_VERSION_CURRENT};
    moduleGlobalVariables = {};
    moduleFuncArray = {};
    functionFuncArray = {};
    moduleFuncParam = {};
    functionFuncParam = {};
    cmdQueue = {};
    cmdList = {};
    allocator = {};

    SUCCESS_OR_TERMINATE(xeDriverInit(XE_INIT_FLAG_NONE));
    xe_device_uuid_t deviceUniqueID = {};
    SUCCESS_OR_TERMINATE(xeDriverGetDevice(&deviceUniqueID, &device0));
    SUCCESS_OR_TERMINATE(xeDeviceGetProperties(device0, &device0Properties));
    if (verbose) {
        printDeviceProperties(device0Properties);
    } else {
        std::cout << device0Properties.device_name << std::endl;
    }

    {
        xe_module_desc_t moduleDesc = {XE_MODULE_DESC_VERSION_CURRENT};
        moduleDesc.format = static_cast<xe_module_format_t>(-1); // -1 for unofficial (debug-only) support llvm as input
        moduleDesc.pInputModule = llvmCodeGlobalVariables;
        moduleDesc.inputSize = static_cast<uint32_t>(strlen(llvmCodeGlobalVariables) + 1);
        SUCCESS_OR_TERMINATE(xeDeviceCreateModule(device0, &moduleDesc, &moduleGlobalVariables, nullptr));
    }

    {
        xe_module_desc_t moduleDesc = {XE_MODULE_DESC_VERSION_CURRENT};
        moduleDesc.format = static_cast<xe_module_format_t>(-1); // -1 for unofficial (debug-only) support llvm as input
        moduleDesc.pInputModule = llvmCodeFuncArray;
        moduleDesc.inputSize = static_cast<uint32_t>(strlen(llvmCodeFuncArray) + 1);
        SUCCESS_OR_TERMINATE(xeDeviceCreateModule(device0, &moduleDesc, &moduleFuncArray, nullptr));
    }

    {
        xe_function_desc_t functionDesc = {XE_FUNCTION_DESC_VERSION_CURRENT};
        functionDesc.pFunctionName = "fptr_array";
        SUCCESS_OR_TERMINATE(xeModuleCreateFunction(moduleFuncArray, &functionDesc, &functionFuncArray));
    }

    {
        xe_module_desc_t moduleDesc = {XE_MODULE_DESC_VERSION_CURRENT};
        moduleDesc.format = static_cast<xe_module_format_t>(-1);                     // -1 for unofficial (debug-only) support llvm as input
        moduleDesc.pInputModule = llvmCodeFuncArray;                                 // llvmCodeFuncParam;
        moduleDesc.inputSize = static_cast<uint32_t>(strlen(llvmCodeFuncArray) + 1); //llvmCodeFuncParam) + 1);
        SUCCESS_OR_TERMINATE(xeDeviceCreateModule(device0, &moduleDesc, &moduleFuncParam, nullptr));
    }

    {
        xe_function_desc_t functionDesc = {XE_FUNCTION_DESC_VERSION_CURRENT};
        functionDesc.pFunctionName = "fptr_array"; //"fptr_param";
        SUCCESS_OR_TERMINATE(xeModuleCreateFunction(moduleFuncParam, &functionDesc, &functionFuncParam));
    }

    {
        xe_command_queue_desc_t cmdQueueDesc = {XE_COMMAND_QUEUE_DESC_VERSION_CURRENT};
        cmdQueueDesc.ordinal = 0;
        cmdQueueDesc.mode = XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;
        SUCCESS_OR_TERMINATE(xeDeviceCreateCommandQueue(device0, &cmdQueueDesc, &cmdQueue));
    }

    {
        xe_command_list_desc_t cmdListDesc = {XE_COMMAND_LIST_DESC_VERSION_CURRENT};
        SUCCESS_OR_TERMINATE(xeDeviceCreateCommandList(device0, &cmdListDesc, &cmdList));
    }

    SUCCESS_OR_TERMINATE(xeCreateMemAllocator(&allocator));
}
