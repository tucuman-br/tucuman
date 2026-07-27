; ModuleID = '/work/benchmark_sem_assertions_com_alinhamento_explicito_v4/I_uint32_t_aligned.bc'
source_filename = "/work/benchmark_sem_assertions_com_alinhamento_explicito_v4/I_uint32_t_aligned.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !18 {
entry:
  %retval = alloca i32, align 4
  %buf = alloca [16 x i8], align 4
  %p = alloca ptr, align 8
  %z = alloca i32, align 4
  store i32 0, ptr %retval, align 4
  call void @llvm.dbg.declare(metadata ptr %buf, metadata !24, metadata !DIExpression()), !dbg !29
  call void @llvm.dbg.declare(metadata ptr %p, metadata !30, metadata !DIExpression()), !dbg !31
  %arraydecay = getelementptr inbounds [16 x i8], ptr %buf, i64 0, i64 0, !dbg !32
  %add.ptr = getelementptr i8, ptr %arraydecay, i64 0, !dbg !33
  store ptr %add.ptr, ptr %p, align 8, !dbg !31
  call void @llvm.dbg.declare(metadata ptr %z, metadata !34, metadata !DIExpression()), !dbg !35
  %0 = load ptr, ptr %p, align 8, !dbg !36
  %1 = load i32, ptr %0, align 4, !dbg !37
  store i32 %1, ptr %z, align 4, !dbg !35
  %2 = load i32, ptr %z, align 4, !dbg !38
  ret i32 0, !dbg !39
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!10, !11, !12, !13, !14, !15, !16}
!llvm.ident = !{!17}

!0 = distinct !DICompileUnit(language: DW_LANG_C11, file: !1, producer: "clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/work/benchmark_sem_assertions_com_alinhamento_explicito_v4/I_uint32_t_aligned.c", directory: "/home/klee", checksumkind: CSK_MD5, checksum: "639be608288b0cd1b5410a9afa76f3da")
!2 = !{!3, !9}
!3 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64)
!4 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !5, line: 26, baseType: !6)
!5 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h", directory: "", checksumkind: CSK_MD5, checksum: "2bf2ae53c58c01b1a1b9383b5195125c")
!6 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint32_t", file: !7, line: 42, baseType: !8)
!7 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "", checksumkind: CSK_MD5, checksum: "d108b5f93a74c50510d7d9bc0ab36df9")
!8 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64)
!10 = !{i32 7, !"Dwarf Version", i32 5}
!11 = !{i32 2, !"Debug Info Version", i32 3}
!12 = !{i32 1, !"wchar_size", i32 4}
!13 = !{i32 8, !"PIC Level", i32 2}
!14 = !{i32 7, !"PIE Level", i32 2}
!15 = !{i32 7, !"uwtable", i32 2}
!16 = !{i32 7, !"frame-pointer", i32 2}
!17 = !{!"clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)"}
!18 = distinct !DISubprogram(name: "main", scope: !19, file: !19, line: 5, type: !20, scopeLine: 5, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !23)
!19 = !DIFile(filename: "/work/benchmark_sem_assertions_com_alinhamento_explicito_v4/I_uint32_t_aligned.c", directory: "", checksumkind: CSK_MD5, checksum: "639be608288b0cd1b5410a9afa76f3da")
!20 = !DISubroutineType(types: !21)
!21 = !{!22}
!22 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!23 = !{}
!24 = !DILocalVariable(name: "buf", scope: !18, file: !19, line: 6, type: !25, align: 32)
!25 = !DICompositeType(tag: DW_TAG_array_type, baseType: !26, size: 128, elements: !27)
!26 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!27 = !{!28}
!28 = !DISubrange(count: 16)
!29 = !DILocation(line: 6, column: 29, scope: !18)
!30 = !DILocalVariable(name: "p", scope: !18, file: !19, line: 7, type: !3)
!31 = !DILocation(line: 7, column: 15, scope: !18)
!32 = !DILocation(line: 7, column: 38, scope: !18)
!33 = !DILocation(line: 7, column: 42, scope: !18)
!34 = !DILocalVariable(name: "z", scope: !18, file: !19, line: 8, type: !4)
!35 = !DILocation(line: 8, column: 14, scope: !18)
!36 = !DILocation(line: 8, column: 19, scope: !18)
!37 = !DILocation(line: 8, column: 18, scope: !18)
!38 = !DILocation(line: 9, column: 11, scope: !18)
!39 = !DILocation(line: 10, column: 5, scope: !18)
