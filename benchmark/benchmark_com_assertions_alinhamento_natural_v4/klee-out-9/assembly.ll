; ModuleID = '/work/benchmark_com_assertions_alinhamento_natural_v4/B_uint32_t_misaligned.bc'
source_filename = "/work/benchmark_com_assertions_alinhamento_natural_v4/B_uint32_t_misaligned.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [37 x i8] c"((uintptr_t)(p) % sizeof(*(p))) == 0\00", align 1, !dbg !0
@.str.1 = private unnamed_addr constant [78 x i8] c"/work/benchmark_com_assertions_alinhamento_natural_v4/B_uint32_t_misaligned.c\00", align 1, !dbg !7
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1, !dbg !12

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !40 {
entry:
  %retval = alloca i32, align 4
  %x = alloca i32, align 4
  %p = alloca ptr, align 8
  %z = alloca i32, align 4
  store i32 0, ptr %retval, align 4
  call void @llvm.dbg.declare(metadata ptr %x, metadata !45, metadata !DIExpression()), !dbg !46
  call void @llvm.dbg.declare(metadata ptr %p, metadata !47, metadata !DIExpression()), !dbg !48
  %add.ptr = getelementptr inbounds i8, ptr %x, i64 1, !dbg !49
  store ptr %add.ptr, ptr %p, align 8, !dbg !48
  call void @llvm.dbg.declare(metadata ptr %z, metadata !50, metadata !DIExpression()), !dbg !51
  %0 = load ptr, ptr %p, align 8, !dbg !52
  %1 = load i32, ptr %0, align 4, !dbg !53
  store i32 %1, ptr %z, align 4, !dbg !51
  %2 = load i32, ptr %z, align 4, !dbg !54
  %3 = load ptr, ptr %p, align 8, !dbg !55
  %4 = ptrtoint ptr %3 to i64, !dbg !55
  %rem = urem i64 %4, 4, !dbg !55
  %cmp = icmp eq i64 %rem, 0, !dbg !55
  br i1 %cmp, label %cond.end, label %cond.false, !dbg !55

cond.false:                                       ; preds = %entry
  call void @__assert_fail(ptr noundef @.str, ptr noundef @.str.1, i32 noundef 10, ptr noundef @__PRETTY_FUNCTION__.main) #3, !dbg !55
  unreachable, !dbg !55

cond.end:                                         ; preds = %entry
  ret i32 0, !dbg !56
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
!llvm.module.flags = !{!32, !33, !34, !35, !36, !37, !38}
!llvm.ident = !{!39}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(scope: null, file: !2, line: 10, type: !3, isLocal: true, isDefinition: true)
!2 = !DIFile(filename: "/work/benchmark_com_assertions_alinhamento_natural_v4/B_uint32_t_misaligned.c", directory: "", checksumkind: CSK_MD5, checksum: "998ee5d2bf31474970bb6a5bc6109677")
!3 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 296, elements: !5)
!4 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!5 = !{!6}
!6 = !DISubrange(count: 37)
!7 = !DIGlobalVariableExpression(var: !8, expr: !DIExpression())
!8 = distinct !DIGlobalVariable(scope: null, file: !2, line: 10, type: !9, isLocal: true, isDefinition: true)
!9 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 624, elements: !10)
!10 = !{!11}
!11 = !DISubrange(count: 78)
!12 = !DIGlobalVariableExpression(var: !13, expr: !DIExpression())
!13 = distinct !DIGlobalVariable(scope: null, file: !2, line: 10, type: !14, isLocal: true, isDefinition: true)
!14 = !DICompositeType(tag: DW_TAG_array_type, baseType: !15, size: 120, elements: !16)
!15 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !4)
!16 = !{!17}
!17 = !DISubrange(count: 15)
!18 = distinct !DICompileUnit(language: DW_LANG_C11, file: !19, producer: "clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !20, globals: !31, splitDebugInlining: false, nameTableKind: None)
!19 = !DIFile(filename: "/work/benchmark_com_assertions_alinhamento_natural_v4/B_uint32_t_misaligned.c", directory: "/home/klee", checksumkind: CSK_MD5, checksum: "998ee5d2bf31474970bb6a5bc6109677")
!20 = !{!21, !27, !28}
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64)
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !23, line: 26, baseType: !24)
!23 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h", directory: "", checksumkind: CSK_MD5, checksum: "2bf2ae53c58c01b1a1b9383b5195125c")
!24 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint32_t", file: !25, line: 42, baseType: !26)
!25 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "", checksumkind: CSK_MD5, checksum: "d108b5f93a74c50510d7d9bc0ab36df9")
!26 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64)
!28 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !29, line: 90, baseType: !30)
!29 = !DIFile(filename: "/usr/include/stdint.h", directory: "", checksumkind: CSK_MD5, checksum: "a48e64edacc5b19f56c99745232c963c")
!30 = !DIBasicType(name: "unsigned long", size: 64, encoding: DW_ATE_unsigned)
!31 = !{!0, !7, !12}
!32 = !{i32 7, !"Dwarf Version", i32 5}
!33 = !{i32 2, !"Debug Info Version", i32 3}
!34 = !{i32 1, !"wchar_size", i32 4}
!35 = !{i32 8, !"PIC Level", i32 2}
!36 = !{i32 7, !"PIE Level", i32 2}
!37 = !{i32 7, !"uwtable", i32 2}
!38 = !{i32 7, !"frame-pointer", i32 2}
!39 = !{!"clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)"}
!40 = distinct !DISubprogram(name: "main", scope: !2, file: !2, line: 5, type: !41, scopeLine: 5, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !18, retainedNodes: !44)
!41 = !DISubroutineType(types: !42)
!42 = !{!43}
!43 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!44 = !{}
!45 = !DILocalVariable(name: "x", scope: !40, file: !2, line: 6, type: !22)
!46 = !DILocation(line: 6, column: 14, scope: !40)
!47 = !DILocalVariable(name: "p", scope: !40, file: !2, line: 7, type: !21)
!48 = !DILocation(line: 7, column: 15, scope: !40)
!49 = !DILocation(line: 7, column: 41, scope: !40)
!50 = !DILocalVariable(name: "z", scope: !40, file: !2, line: 8, type: !22)
!51 = !DILocation(line: 8, column: 14, scope: !40)
!52 = !DILocation(line: 8, column: 19, scope: !40)
!53 = !DILocation(line: 8, column: 18, scope: !40)
!54 = !DILocation(line: 9, column: 11, scope: !40)
!55 = !DILocation(line: 10, column: 5, scope: !40)
!56 = !DILocation(line: 11, column: 5, scope: !40)
