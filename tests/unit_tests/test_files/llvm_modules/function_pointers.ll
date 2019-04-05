; ------------------------------------------------
; OCL_asm634fdde2f8eda9a3_beforeUnification.ll
; ------------------------------------------------
source_filename = "<origin>"
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-f80:128:128-v16:16:16-v24:32:32-v32:32:32-v48:64:64-v64:64:64-v96:128:128-v128:128:128-v192:256:256-v256:256:256-v512:512:512-v1024:1024:1024-f80:128:128-n8:16:32"
target triple = "unknown64-unknown-unknown"

@sgv = internal constant [5 x i8] c"2000\00"
@fgv = internal constant [0 x i8] zeroinitializer
@lvgv = internal constant [0 x i8 addrspace(3)*] zeroinitializer
@llvm.global.annotations = appending global [1 x { i8*, i8*, i8*, i8*, i32 }] [{ i8*, i8*, i8*, i8*, i32 } { i8* bitcast (void (i32 addrspace(1)*, i32, i32, i32)* @testStackCallMain to i8*), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @sgv, i32 0, i32 0), i8* getelementptr inbounds ([0 x i8], [0 x i8]* @fgv, i32 0, i32 0), i8* bitcast ([0 x i8 addrspace(3)*]* @lvgv to i8*), i32 0 }], section "llvm.metadata"

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
define void @testStackCallMain(i32 addrspace(1)* %dst, i32 %a, i32 %b, i32 %comp) #0 {
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
  %result3 = call i32 @add(i32 %result, i32 5)
  store i32 %result3, i32 addrspace(1)* %dst, align 4
  ret void
}

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-realign-stack" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!opencl.kernels = !{!0}
!llvm.ident = !{!4}
!igc.input.ir = !{}
!igc.functions = !{}
!IGCMetadata = !{!5}

!0 = !{void (i32 addrspace(1)*, i32, i32, i32)* @testStackCallMain, !1}
!1 = !{!"apple.cl.arg_metadata", !2, !3, !3, !3}
!2 = !{!"stream", !"write", !"global"}
!3 = !{}
!4 = !{!"Apple LLVM version 6.0.0 (clang-3600.13.14) (based on LLVM 3.5svn)"}
!5 = !{!"ModuleMD", !6, !7, !29, !30, !50, !52, !65, !71, !79, !81, !82, !83, !85, !86, !87, !88, !89, !90, !91, !93, !97, !98, !99, !100}
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
!100 = !{!"m_ShaderResourceViewMcsMask", !101, !102}
!101 = !{!"m_ShaderResourceViewMcsMaskVec[0]", i64 0}
!102 = !{!"m_ShaderResourceViewMcsMaskVec[1]", i64 0}
