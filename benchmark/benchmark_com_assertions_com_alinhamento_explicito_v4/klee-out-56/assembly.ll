; ModuleID = '/work/benchmark_com_assertions_com_alinhamento_explicito_v4/J_uint32_t_misaligned.bc'
source_filename = "/work/benchmark_com_assertions_com_alinhamento_explicito_v4/J_uint32_t_misaligned.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.packed_s = type <{ i8, i32 }>

@.str = private unnamed_addr constant [37 x i8] c"((uintptr_t)(q) % sizeof(*(q))) == 0\00", align 1, !dbg !0
@.str.1 = private unnamed_addr constant [84 x i8] c"/work/benchmark_com_assertions_com_alinhamento_explicito_v4/J_uint32_t_misaligned.c\00", align 1, !dbg !7
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1, !dbg !12

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !39 {
entry:
  %retval = alloca i32, align 4
  %obj = alloca %struct.packed_s, align 4
  %ptr = alloca ptr, align 8
  %q = alloca ptr, align 8
  %z = alloca i32, align 4
  store i32 0, ptr %retval, align 4
  call void @llvm.dbg.declare(metadata ptr %obj, metadata !44, metadata !DIExpression()), !dbg !49
  call void @llvm.dbg.declare(metadata ptr %ptr, metadata !50, metadata !DIExpression()), !dbg !52
  store ptr %obj, ptr %ptr, align 8, !dbg !52
  call void @llvm.dbg.declare(metadata ptr %q, metadata !53, metadata !DIExpression()), !dbg !54
  %0 = load ptr, ptr %ptr, align 8, !dbg !55
  %b = getelementptr inbounds %struct.packed_s, ptr %0, i32 0, i32 1, !dbg !56
  store ptr %b, ptr %q, align 8, !dbg !54
  call void @llvm.dbg.declare(metadata ptr %z, metadata !57, metadata !DIExpression()), !dbg !58
  %1 = load ptr, ptr %q, align 8, !dbg !59
  %2 = load i32, ptr %1, align 4, !dbg !60
  store i32 %2, ptr %z, align 4, !dbg !58
  %3 = load i32, ptr %z, align 4, !dbg !61
  %4 = load ptr, ptr %q, align 8, !dbg !62
  %5 = ptrtoint ptr %4 to i64, !dbg !62
  %rem = urem i64 %5, 4, !dbg !62
  %cmp = icmp eq i64 %rem, 0, !dbg !62
  br i1 %cmp, label %cond.end, label %cond.false, !dbg !62

cond.false:                                       ; preds = %entry
  call void @__assert_fail(ptr noundef @.str, ptr noundef @.str.1, i32 noundef 22, ptr noundef @__PRETTY_FUNCTION__.main) #3, !dbg !62
  unreachable, !dbg !62

cond.end:                                         ; preds = %entry
  ret i32 0, !dbg !63
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
!1 = distinct !DIGlobalVariable(scope: null, file: !2, line: 22, type: !3, isLocal: true, isDefinition: true)
!2 = !DIFile(filename: "/work/benchmark_com_assertions_com_alinhamento_explicito_v4/J_uint32_t_misaligned.c", directory: "", checksumkind: CSK_MD5, checksum: "a6d9913252e4b73ff33fa9b43d8ef026")
!3 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 296, elements: !5)
!4 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!5 = !{!6}
!6 = !DISubrange(count: 37)
!7 = !DIGlobalVariableExpression(var: !8, expr: !DIExpression())
!8 = distinct !DIGlobalVariable(scope: null, file: !2, line: 22, type: !9, isLocal: true, isDefinition: true)
!9 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 672, elements: !10)
!10 = !{!11}
!11 = !DISubrange(count: 84)
!12 = !DIGlobalVariableExpression(var: !13, expr: !DIExpression())
!13 = distinct !DIGlobalVariable(scope: null, file: !2, line: 22, type: !14, isLocal: true, isDefinition: true)
!14 = !DICompositeType(tag: DW_TAG_array_type, baseType: !15, size: 120, elements: !16)
!15 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !4)
!16 = !{!17}
!17 = !DISubrange(count: 15)
!18 = distinct !DICompileUnit(language: DW_LANG_C11, file: !19, producer: "clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !20, globals: !30, splitDebugInlining: false, nameTableKind: None)
!19 = !DIFile(filename: "/work/benchmark_com_assertions_com_alinhamento_explicito_v4/J_uint32_t_misaligned.c", directory: "/home/klee", checksumkind: CSK_MD5, checksum: "a6d9913252e4b73ff33fa9b43d8ef026")
!20 = !{!21, !27}
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64)
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !23, line: 26, baseType: !24)
!23 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h", directory: "", checksumkind: CSK_MD5, checksum: "2bf2ae53c58c01b1a1b9383b5195125c")
!24 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint32_t", file: !25, line: 42, baseType: !26)
!25 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "", checksumkind: CSK_MD5, checksum: "d108b5f93a74c50510d7d9bc0ab36df9")
!26 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!27 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !28, line: 90, baseType: !29)
!28 = !DIFile(filename: "/usr/include/stdint.h", directory: "", checksumkind: CSK_MD5, checksum: "a48e64edacc5b19f56c99745232c963c")
!29 = !DIBasicType(name: "unsigned long", size: 64, encoding: DW_ATE_unsigned)
!30 = !{!0, !7, !12}
!31 = !{i32 7, !"Dwarf Version", i32 5}
!32 = !{i32 2, !"Debug Info Version", i32 3}
!33 = !{i32 1, !"wchar_size", i32 4}
!34 = !{i32 8, !"PIC Level", i32 2}
!35 = !{i32 7, !"PIE Level", i32 2}
!36 = !{i32 7, !"uwtable", i32 2}
!37 = !{i32 7, !"frame-pointer", i32 2}
!38 = !{!"clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)"}
!39 = distinct !DISubprogram(name: "main", scope: !2, file: !2, line: 16, type: !40, scopeLine: 16, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !18, retainedNodes: !43)
!40 = !DISubroutineType(types: !41)
!41 = !{!42}
!42 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!43 = !{}
!44 = !DILocalVariable(name: "obj", scope: !39, file: !2, line: 17, type: !45, align: 32)
!45 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "packed_s", file: !2, line: 9, size: 40, elements: !46)
!46 = !{!47, !48}
!47 = !DIDerivedType(tag: DW_TAG_member, name: "a", scope: !45, file: !2, line: 10, baseType: !4, size: 8)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "b", scope: !45, file: !2, line: 11, baseType: !22, size: 32, offset: 8)
!49 = !DILocation(line: 17, column: 40, scope: !39)
!50 = !DILocalVariable(name: "ptr", scope: !39, file: !2, line: 18, type: !51)
!51 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64)
!52 = !DILocation(line: 18, column: 22, scope: !39)
!53 = !DILocalVariable(name: "q", scope: !39, file: !2, line: 19, type: !21)
!54 = !DILocation(line: 19, column: 15, scope: !39)
!55 = !DILocation(line: 19, column: 33, scope: !39)
!56 = !DILocation(line: 19, column: 38, scope: !39)
!57 = !DILocalVariable(name: "z", scope: !39, file: !2, line: 20, type: !22)
!58 = !DILocation(line: 20, column: 14, scope: !39)
!59 = !DILocation(line: 20, column: 20, scope: !39)
!60 = !DILocation(line: 20, column: 19, scope: !39)
!61 = !DILocation(line: 21, column: 11, scope: !39)
!62 = !DILocation(line: 22, column: 5, scope: !39)
!63 = !DILocation(line: 23, column: 5, scope: !39)
