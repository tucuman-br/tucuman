; ModuleID = '/work/benchmark_com_assertions_com_alinhamento_explicito_v4/B_uint64_t_aligned.bc'
source_filename = "/work/benchmark_com_assertions_com_alinhamento_explicito_v4/B_uint64_t_aligned.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [37 x i8] c"((uintptr_t)(p) % sizeof(*(p))) == 0\00", align 1, !dbg !0
@.str.1 = private unnamed_addr constant [81 x i8] c"/work/benchmark_com_assertions_com_alinhamento_explicito_v4/B_uint64_t_aligned.c\00", align 1, !dbg !7
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1, !dbg !12

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !39 {
entry:
  %retval = alloca i32, align 4
  %x = alloca i64, align 8
  %p = alloca ptr, align 8
  %z = alloca i64, align 8
  store i32 0, ptr %retval, align 4
  call void @llvm.dbg.declare(metadata ptr %x, metadata !44, metadata !DIExpression()), !dbg !45
  call void @llvm.dbg.declare(metadata ptr %p, metadata !46, metadata !DIExpression()), !dbg !47
  %add.ptr = getelementptr inbounds i8, ptr %x, i64 0, !dbg !48
  store ptr %add.ptr, ptr %p, align 8, !dbg !47
  call void @llvm.dbg.declare(metadata ptr %z, metadata !49, metadata !DIExpression()), !dbg !50
  %0 = load ptr, ptr %p, align 8, !dbg !51
  %1 = load i64, ptr %0, align 8, !dbg !52
  store i64 %1, ptr %z, align 8, !dbg !50
  %2 = load i64, ptr %z, align 8, !dbg !53
  %3 = load ptr, ptr %p, align 8, !dbg !54
  %4 = ptrtoint ptr %3 to i64, !dbg !54
  %rem = urem i64 %4, 8, !dbg !54
  %cmp = icmp eq i64 %rem, 0, !dbg !54
  br i1 %cmp, label %cond.end, label %cond.false, !dbg !54

cond.false:                                       ; preds = %entry
  call void @__assert_fail(ptr noundef @.str, ptr noundef @.str.1, i32 noundef 10, ptr noundef @__PRETTY_FUNCTION__.main) #3, !dbg !54
  unreachable, !dbg !54

cond.end:                                         ; preds = %entry
  ret i32 0, !dbg !55
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noreturn nounwind
declare void @__assert_fail(ptr noundef, ptr noundef, i32 noundef, ptr noundef) #2

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #2 = { noreturn nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { noreturn nounwind }

!llvm.dbg.cu = !{!18}
!llvm.module.flags = !{!31, !32, !33, !34, !35, !36, !37}
!llvm.ident = !{!38}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(scope: null, file: !2, line: 10, type: !3, isLocal: true, isDefinition: true)
!2 = !DIFile(filename: "/work/benchmark_com_assertions_com_alinhamento_explicito_v4/B_uint64_t_aligned.c", directory: "", checksumkind: CSK_MD5, checksum: "c3915dcab0aee945a1643094e26d00e6")
!3 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 296, elements: !5)
!4 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!5 = !{!6}
!6 = !DISubrange(count: 37)
!7 = !DIGlobalVariableExpression(var: !8, expr: !DIExpression())
!8 = distinct !DIGlobalVariable(scope: null, file: !2, line: 10, type: !9, isLocal: true, isDefinition: true)
!9 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 648, elements: !10)
!10 = !{!11}
!11 = !DISubrange(count: 81)
!12 = !DIGlobalVariableExpression(var: !13, expr: !DIExpression())
!13 = distinct !DIGlobalVariable(scope: null, file: !2, line: 10, type: !14, isLocal: true, isDefinition: true)
!14 = !DICompositeType(tag: DW_TAG_array_type, baseType: !15, size: 120, elements: !16)
!15 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !4)
!16 = !{!17}
!17 = !DISubrange(count: 15)
!18 = distinct !DICompileUnit(language: DW_LANG_C11, file: !19, producer: "clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !20, globals: !30, splitDebugInlining: false, nameTableKind: None)
!19 = !DIFile(filename: "/work/benchmark_com_assertions_com_alinhamento_explicito_v4/B_uint64_t_aligned.c", directory: "/home/klee", checksumkind: CSK_MD5, checksum: "c3915dcab0aee945a1643094e26d00e6")
!20 = !{!21, !27, !28}
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64)
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !23, line: 27, baseType: !24)
!23 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h", directory: "", checksumkind: CSK_MD5, checksum: "2bf2ae53c58c01b1a1b9383b5195125c")
!24 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint64_t", file: !25, line: 45, baseType: !26)
!25 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "", checksumkind: CSK_MD5, checksum: "d108b5f93a74c50510d7d9bc0ab36df9")
!26 = !DIBasicType(name: "unsigned long", size: 64, encoding: DW_ATE_unsigned)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64)
!28 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !29, line: 90, baseType: !26)
!29 = !DIFile(filename: "/usr/include/stdint.h", directory: "", checksumkind: CSK_MD5, checksum: "a48e64edacc5b19f56c99745232c963c")
!30 = !{!0, !7, !12}
!31 = !{i32 7, !"Dwarf Version", i32 5}
!32 = !{i32 2, !"Debug Info Version", i32 3}
!33 = !{i32 1, !"wchar_size", i32 4}
!34 = !{i32 8, !"PIC Level", i32 2}
!35 = !{i32 7, !"PIE Level", i32 2}
!36 = !{i32 7, !"uwtable", i32 2}
!37 = !{i32 7, !"frame-pointer", i32 2}
!38 = !{!"clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)"}
!39 = distinct !DISubprogram(name: "main", scope: !2, file: !2, line: 5, type: !40, scopeLine: 5, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !18, retainedNodes: !43)
!40 = !DISubroutineType(types: !41)
!41 = !{!42}
!42 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!43 = !{}
!44 = !DILocalVariable(name: "x", scope: !39, file: !2, line: 6, type: !22, align: 64)
!45 = !DILocation(line: 6, column: 33, scope: !39)
!46 = !DILocalVariable(name: "p", scope: !39, file: !2, line: 7, type: !21)
!47 = !DILocation(line: 7, column: 15, scope: !39)
!48 = !DILocation(line: 7, column: 41, scope: !39)
!49 = !DILocalVariable(name: "z", scope: !39, file: !2, line: 8, type: !22)
!50 = !DILocation(line: 8, column: 14, scope: !39)
!51 = !DILocation(line: 8, column: 19, scope: !39)
!52 = !DILocation(line: 8, column: 18, scope: !39)
!53 = !DILocation(line: 9, column: 11, scope: !39)
!54 = !DILocation(line: 10, column: 5, scope: !39)
!55 = !DILocation(line: 11, column: 5, scope: !39)
