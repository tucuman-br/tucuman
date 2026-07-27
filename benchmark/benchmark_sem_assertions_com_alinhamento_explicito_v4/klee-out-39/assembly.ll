; ModuleID = '/work/benchmark_sem_assertions_com_alinhamento_explicito_v4/G_uint32_t_misaligned.bc'
source_filename = "/work/benchmark_sem_assertions_com_alinhamento_explicito_v4/G_uint32_t_misaligned.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !17 {
entry:
  %retval = alloca i32, align 4
  %buf = alloca [64 x i8], align 4
  %p = alloca ptr, align 8
  %z = alloca i32, align 4
  store i32 0, ptr %retval, align 4
  call void @llvm.dbg.declare(metadata ptr %buf, metadata !23, metadata !DIExpression()), !dbg !28
  call void @llvm.dbg.declare(metadata ptr %p, metadata !29, metadata !DIExpression()), !dbg !30
  %arraydecay = getelementptr inbounds [64 x i8], ptr %buf, i64 0, i64 0, !dbg !31
  %add.ptr = getelementptr inbounds i8, ptr %arraydecay, i64 49, !dbg !32
  store ptr %add.ptr, ptr %p, align 8, !dbg !30
  call void @llvm.dbg.declare(metadata ptr %z, metadata !33, metadata !DIExpression()), !dbg !34
  %0 = load ptr, ptr %p, align 8, !dbg !35
  %1 = load i32, ptr %0, align 4, !dbg !36
  store i32 %1, ptr %z, align 4, !dbg !34
  %2 = load i32, ptr %z, align 4, !dbg !37
  ret i32 0, !dbg !38
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!9, !10, !11, !12, !13, !14, !15}
!llvm.ident = !{!16}

!0 = distinct !DICompileUnit(language: DW_LANG_C11, file: !1, producer: "clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/work/benchmark_sem_assertions_com_alinhamento_explicito_v4/G_uint32_t_misaligned.c", directory: "/home/klee", checksumkind: CSK_MD5, checksum: "4a5b06cb310c418a5265cbe89420d942")
!2 = !{!3}
!3 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64)
!4 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !5, line: 26, baseType: !6)
!5 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h", directory: "", checksumkind: CSK_MD5, checksum: "2bf2ae53c58c01b1a1b9383b5195125c")
!6 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint32_t", file: !7, line: 42, baseType: !8)
!7 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "", checksumkind: CSK_MD5, checksum: "d108b5f93a74c50510d7d9bc0ab36df9")
!8 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!9 = !{i32 7, !"Dwarf Version", i32 5}
!10 = !{i32 2, !"Debug Info Version", i32 3}
!11 = !{i32 1, !"wchar_size", i32 4}
!12 = !{i32 8, !"PIC Level", i32 2}
!13 = !{i32 7, !"PIE Level", i32 2}
!14 = !{i32 7, !"uwtable", i32 2}
!15 = !{i32 7, !"frame-pointer", i32 2}
!16 = !{!"clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)"}
!17 = distinct !DISubprogram(name: "main", scope: !18, file: !18, line: 5, type: !19, scopeLine: 5, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !22)
!18 = !DIFile(filename: "/work/benchmark_sem_assertions_com_alinhamento_explicito_v4/G_uint32_t_misaligned.c", directory: "", checksumkind: CSK_MD5, checksum: "4a5b06cb310c418a5265cbe89420d942")
!19 = !DISubroutineType(types: !20)
!20 = !{!21}
!21 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!22 = !{}
!23 = !DILocalVariable(name: "buf", scope: !17, file: !18, line: 6, type: !24, align: 32)
!24 = !DICompositeType(tag: DW_TAG_array_type, baseType: !25, size: 512, elements: !26)
!25 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!26 = !{!27}
!27 = !DISubrange(count: 64)
!28 = !DILocation(line: 6, column: 30, scope: !17)
!29 = !DILocalVariable(name: "p", scope: !17, file: !18, line: 7, type: !3)
!30 = !DILocation(line: 7, column: 15, scope: !17)
!31 = !DILocation(line: 7, column: 31, scope: !17)
!32 = !DILocation(line: 7, column: 35, scope: !17)
!33 = !DILocalVariable(name: "z", scope: !17, file: !18, line: 8, type: !4)
!34 = !DILocation(line: 8, column: 14, scope: !17)
!35 = !DILocation(line: 8, column: 19, scope: !17)
!36 = !DILocation(line: 8, column: 18, scope: !17)
!37 = !DILocation(line: 9, column: 11, scope: !17)
!38 = !DILocation(line: 10, column: 5, scope: !17)
