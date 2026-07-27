; ModuleID = '/work/benchmark_sem_assertions_com_alinhamento_explicito_v4/B_uint16_t_aligned.bc'
source_filename = "/work/benchmark_sem_assertions_com_alinhamento_explicito_v4/B_uint16_t_aligned.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !19 {
entry:
  %retval = alloca i32, align 4
  %x = alloca i16, align 2
  %p = alloca ptr, align 8
  %z = alloca i16, align 2
  store i32 0, ptr %retval, align 4
  call void @llvm.dbg.declare(metadata ptr %x, metadata !25, metadata !DIExpression()), !dbg !26
  call void @llvm.dbg.declare(metadata ptr %p, metadata !27, metadata !DIExpression()), !dbg !28
  %add.ptr = getelementptr inbounds i8, ptr %x, i64 0, !dbg !29
  store ptr %add.ptr, ptr %p, align 8, !dbg !28
  call void @llvm.dbg.declare(metadata ptr %z, metadata !30, metadata !DIExpression()), !dbg !31
  %0 = load ptr, ptr %p, align 8, !dbg !32
  %1 = load i16, ptr %0, align 2, !dbg !33
  store i16 %1, ptr %z, align 2, !dbg !31
  %2 = load i16, ptr %z, align 2, !dbg !34
  ret i32 0, !dbg !35
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!11, !12, !13, !14, !15, !16, !17}
!llvm.ident = !{!18}

!0 = distinct !DICompileUnit(language: DW_LANG_C11, file: !1, producer: "clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/work/benchmark_sem_assertions_com_alinhamento_explicito_v4/B_uint16_t_aligned.c", directory: "/home/klee", checksumkind: CSK_MD5, checksum: "e46b049875cca7c4998ab919337a9dfd")
!2 = !{!3, !9}
!3 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64)
!4 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !5, line: 25, baseType: !6)
!5 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h", directory: "", checksumkind: CSK_MD5, checksum: "2bf2ae53c58c01b1a1b9383b5195125c")
!6 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint16_t", file: !7, line: 40, baseType: !8)
!7 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "", checksumkind: CSK_MD5, checksum: "d108b5f93a74c50510d7d9bc0ab36df9")
!8 = !DIBasicType(name: "unsigned short", size: 16, encoding: DW_ATE_unsigned)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!10 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!11 = !{i32 7, !"Dwarf Version", i32 5}
!12 = !{i32 2, !"Debug Info Version", i32 3}
!13 = !{i32 1, !"wchar_size", i32 4}
!14 = !{i32 8, !"PIC Level", i32 2}
!15 = !{i32 7, !"PIE Level", i32 2}
!16 = !{i32 7, !"uwtable", i32 2}
!17 = !{i32 7, !"frame-pointer", i32 2}
!18 = !{!"clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)"}
!19 = distinct !DISubprogram(name: "main", scope: !20, file: !20, line: 5, type: !21, scopeLine: 5, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !24)
!20 = !DIFile(filename: "/work/benchmark_sem_assertions_com_alinhamento_explicito_v4/B_uint16_t_aligned.c", directory: "", checksumkind: CSK_MD5, checksum: "e46b049875cca7c4998ab919337a9dfd")
!21 = !DISubroutineType(types: !22)
!22 = !{!23}
!23 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!24 = !{}
!25 = !DILocalVariable(name: "x", scope: !19, file: !20, line: 6, type: !4)
!26 = !DILocation(line: 6, column: 14, scope: !19)
!27 = !DILocalVariable(name: "p", scope: !19, file: !20, line: 7, type: !3)
!28 = !DILocation(line: 7, column: 15, scope: !19)
!29 = !DILocation(line: 7, column: 41, scope: !19)
!30 = !DILocalVariable(name: "z", scope: !19, file: !20, line: 8, type: !4)
!31 = !DILocation(line: 8, column: 14, scope: !19)
!32 = !DILocation(line: 8, column: 19, scope: !19)
!33 = !DILocation(line: 8, column: 18, scope: !19)
!34 = !DILocation(line: 9, column: 11, scope: !19)
!35 = !DILocation(line: 10, column: 5, scope: !19)
