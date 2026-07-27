; ModuleID = '/work/benchmark_sem_assertions_alinhamento_natural_v4/D_uint64_t_misaligned.bc'
source_filename = "/work/benchmark_sem_assertions_alinhamento_natural_v4/D_uint64_t_misaligned.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.S = type { i8, i64 }

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !19 {
entry:
  %retval = alloca i32, align 4
  %s = alloca %struct.S, align 8
  %base = alloca ptr, align 8
  %p = alloca ptr, align 8
  %z = alloca i64, align 8
  store i32 0, ptr %retval, align 4
  call void @llvm.dbg.declare(metadata ptr %s, metadata !25, metadata !DIExpression()), !dbg !30
  call void @llvm.dbg.declare(metadata ptr %base, metadata !31, metadata !DIExpression()), !dbg !32
  store ptr %s, ptr %base, align 8, !dbg !32
  call void @llvm.dbg.declare(metadata ptr %p, metadata !33, metadata !DIExpression()), !dbg !34
  %0 = load ptr, ptr %base, align 8, !dbg !35
  %add.ptr = getelementptr inbounds i8, ptr %0, i64 1, !dbg !36
  store ptr %add.ptr, ptr %p, align 8, !dbg !34
  call void @llvm.dbg.declare(metadata ptr %z, metadata !37, metadata !DIExpression()), !dbg !38
  %1 = load ptr, ptr %p, align 8, !dbg !39
  %2 = load i64, ptr %1, align 8, !dbg !40
  store i64 %2, ptr %z, align 8, !dbg !38
  %3 = load i64, ptr %z, align 8, !dbg !41
  ret i32 0, !dbg !42
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!11, !12, !13, !14, !15, !16, !17}
!llvm.ident = !{!18}

!0 = distinct !DICompileUnit(language: DW_LANG_C11, file: !1, producer: "clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/work/benchmark_sem_assertions_alinhamento_natural_v4/D_uint64_t_misaligned.c", directory: "/home/klee", checksumkind: CSK_MD5, checksum: "aae01a6852b0b3dee558440a18f9b783")
!2 = !{!3, !5}
!3 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64)
!4 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64)
!6 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !7, line: 27, baseType: !8)
!7 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h", directory: "", checksumkind: CSK_MD5, checksum: "2bf2ae53c58c01b1a1b9383b5195125c")
!8 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint64_t", file: !9, line: 45, baseType: !10)
!9 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "", checksumkind: CSK_MD5, checksum: "d108b5f93a74c50510d7d9bc0ab36df9")
!10 = !DIBasicType(name: "unsigned long", size: 64, encoding: DW_ATE_unsigned)
!11 = !{i32 7, !"Dwarf Version", i32 5}
!12 = !{i32 2, !"Debug Info Version", i32 3}
!13 = !{i32 1, !"wchar_size", i32 4}
!14 = !{i32 8, !"PIC Level", i32 2}
!15 = !{i32 7, !"PIE Level", i32 2}
!16 = !{i32 7, !"uwtable", i32 2}
!17 = !{i32 7, !"frame-pointer", i32 2}
!18 = !{!"clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)"}
!19 = distinct !DISubprogram(name: "main", scope: !20, file: !20, line: 7, type: !21, scopeLine: 7, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !24)
!20 = !DIFile(filename: "/work/benchmark_sem_assertions_alinhamento_natural_v4/D_uint64_t_misaligned.c", directory: "", checksumkind: CSK_MD5, checksum: "aae01a6852b0b3dee558440a18f9b783")
!21 = !DISubroutineType(types: !22)
!22 = !{!23}
!23 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!24 = !{}
!25 = !DILocalVariable(name: "s", scope: !19, file: !20, line: 8, type: !26)
!26 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "S", file: !20, line: 5, size: 128, elements: !27)
!27 = !{!28, !29}
!28 = !DIDerivedType(tag: DW_TAG_member, name: "a", scope: !26, file: !20, line: 5, baseType: !4, size: 8)
!29 = !DIDerivedType(tag: DW_TAG_member, name: "b", scope: !26, file: !20, line: 5, baseType: !6, size: 64, offset: 64)
!30 = !DILocation(line: 8, column: 14, scope: !19)
!31 = !DILocalVariable(name: "base", scope: !19, file: !20, line: 9, type: !3)
!32 = !DILocation(line: 9, column: 11, scope: !19)
!33 = !DILocalVariable(name: "p", scope: !19, file: !20, line: 12, type: !5)
!34 = !DILocation(line: 12, column: 15, scope: !19)
!35 = !DILocation(line: 12, column: 31, scope: !19)
!36 = !DILocation(line: 12, column: 36, scope: !19)
!37 = !DILocalVariable(name: "z", scope: !19, file: !20, line: 13, type: !6)
!38 = !DILocation(line: 13, column: 14, scope: !19)
!39 = !DILocation(line: 13, column: 19, scope: !19)
!40 = !DILocation(line: 13, column: 18, scope: !19)
!41 = !DILocation(line: 14, column: 11, scope: !19)
!42 = !DILocation(line: 15, column: 5, scope: !19)
