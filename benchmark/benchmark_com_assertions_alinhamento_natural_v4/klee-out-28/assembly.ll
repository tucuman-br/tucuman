; ModuleID = '/work/benchmark_com_assertions_alinhamento_natural_v4/E_uint64_t_aligned.bc'
source_filename = "/work/benchmark_com_assertions_alinhamento_natural_v4/E_uint64_t_aligned.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [37 x i8] c"((uintptr_t)(p) % sizeof(*(p))) == 0\00", align 1, !dbg !0
@.str.1 = private unnamed_addr constant [75 x i8] c"/work/benchmark_com_assertions_alinhamento_natural_v4/E_uint64_t_aligned.c\00", align 1, !dbg !7
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1, !dbg !12
@.str.2 = private unnamed_addr constant [12 x i8] c"nondet_uint\00", align 1, !dbg !18

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !44 {
entry:
  %retval = alloca i32, align 4
  %buf = alloca [64 x i8], align 16
  %k = alloca i32, align 4
  %p = alloca ptr, align 8
  %z = alloca i64, align 8
  store i32 0, ptr %retval, align 4
  call void @llvm.dbg.declare(metadata ptr %buf, metadata !49, metadata !DIExpression()), !dbg !53
  call void @llvm.dbg.declare(metadata ptr %k, metadata !54, metadata !DIExpression()), !dbg !56
  %call = call i32 @VERIFIER_nondet_uint(), !dbg !57
  %rem = urem i32 %call, 6, !dbg !58
  store i32 %rem, ptr %k, align 4, !dbg !56
  call void @llvm.dbg.declare(metadata ptr %p, metadata !59, metadata !DIExpression()), !dbg !60
  %arraydecay = getelementptr inbounds [64 x i8], ptr %buf, i64 0, i64 0, !dbg !61
  %0 = load i32, ptr %k, align 4, !dbg !62
  %conv = zext i32 %0 to i64, !dbg !62
  %mul = mul i64 %conv, 8, !dbg !63
  %add.ptr = getelementptr inbounds i8, ptr %arraydecay, i64 %mul, !dbg !64
  store ptr %add.ptr, ptr %p, align 8, !dbg !60
  call void @llvm.dbg.declare(metadata ptr %z, metadata !65, metadata !DIExpression()), !dbg !66
  %1 = load ptr, ptr %p, align 8, !dbg !67
  %2 = load i64, ptr %1, align 8, !dbg !68
  store i64 %2, ptr %z, align 8, !dbg !66
  %3 = load i64, ptr %z, align 8, !dbg !69
  %4 = load ptr, ptr %p, align 8, !dbg !70
  %5 = ptrtoint ptr %4 to i64, !dbg !70
  %rem1 = urem i64 %5, 8, !dbg !70
  %cmp = icmp eq i64 %rem1, 0, !dbg !70
  br i1 %cmp, label %cond.end, label %cond.false, !dbg !70

cond.false:                                       ; preds = %entry
  call void @__assert_fail(ptr noundef @.str, ptr noundef @.str.1, i32 noundef 12, ptr noundef @__PRETTY_FUNCTION__.main) #4, !dbg !70
  unreachable, !dbg !70

cond.end:                                         ; preds = %entry
  ret i32 0, !dbg !71
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind uwtable
define internal i32 @VERIFIER_nondet_uint() #0 !dbg !72 {
entry:
  %x = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %x, metadata !75, metadata !DIExpression()), !dbg !76
  call void @klee_make_symbolic(ptr noundef %x, i64 noundef 4, ptr noundef @.str.2), !dbg !77
  %0 = load i32, ptr %x, align 4, !dbg !78
  ret i32 %0, !dbg !79
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(ptr noundef, ptr noundef, i32 noundef, ptr noundef) #2

declare void @klee_make_symbolic(ptr noundef, i64 noundef, ptr noundef) #3

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #2 = { noreturn nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { noreturn nounwind }

!llvm.dbg.cu = !{!24}
!llvm.module.flags = !{!36, !37, !38, !39, !40, !41, !42}
!llvm.ident = !{!43}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(scope: null, file: !2, line: 12, type: !3, isLocal: true, isDefinition: true)
!2 = !DIFile(filename: "/work/benchmark_com_assertions_alinhamento_natural_v4/E_uint64_t_aligned.c", directory: "", checksumkind: CSK_MD5, checksum: "4715845418261d9d1b09a2fb4fc17688")
!3 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 296, elements: !5)
!4 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!5 = !{!6}
!6 = !DISubrange(count: 37)
!7 = !DIGlobalVariableExpression(var: !8, expr: !DIExpression())
!8 = distinct !DIGlobalVariable(scope: null, file: !2, line: 12, type: !9, isLocal: true, isDefinition: true)
!9 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 600, elements: !10)
!10 = !{!11}
!11 = !DISubrange(count: 75)
!12 = !DIGlobalVariableExpression(var: !13, expr: !DIExpression())
!13 = distinct !DIGlobalVariable(scope: null, file: !2, line: 12, type: !14, isLocal: true, isDefinition: true)
!14 = !DICompositeType(tag: DW_TAG_array_type, baseType: !15, size: 120, elements: !16)
!15 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !4)
!16 = !{!17}
!17 = !DISubrange(count: 15)
!18 = !DIGlobalVariableExpression(var: !19, expr: !DIExpression())
!19 = distinct !DIGlobalVariable(scope: null, file: !20, line: 117, type: !21, isLocal: true, isDefinition: true)
!20 = !DIFile(filename: "/work/benchmark_com_assertions_alinhamento_natural_v4/verifier.h", directory: "", checksumkind: CSK_MD5, checksum: "067d54c60d1b3554bee88b305f379a99")
!21 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 96, elements: !22)
!22 = !{!23}
!23 = !DISubrange(count: 12)
!24 = distinct !DICompileUnit(language: DW_LANG_C11, file: !25, producer: "clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !26, globals: !35, splitDebugInlining: false, nameTableKind: None)
!25 = !DIFile(filename: "/work/benchmark_com_assertions_alinhamento_natural_v4/E_uint64_t_aligned.c", directory: "/home/klee", checksumkind: CSK_MD5, checksum: "4715845418261d9d1b09a2fb4fc17688")
!26 = !{!27, !33}
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64)
!28 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !29, line: 27, baseType: !30)
!29 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h", directory: "", checksumkind: CSK_MD5, checksum: "2bf2ae53c58c01b1a1b9383b5195125c")
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint64_t", file: !31, line: 45, baseType: !32)
!31 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "", checksumkind: CSK_MD5, checksum: "d108b5f93a74c50510d7d9bc0ab36df9")
!32 = !DIBasicType(name: "unsigned long", size: 64, encoding: DW_ATE_unsigned)
!33 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !34, line: 90, baseType: !32)
!34 = !DIFile(filename: "/usr/include/stdint.h", directory: "", checksumkind: CSK_MD5, checksum: "a48e64edacc5b19f56c99745232c963c")
!35 = !{!0, !7, !12, !18}
!36 = !{i32 7, !"Dwarf Version", i32 5}
!37 = !{i32 2, !"Debug Info Version", i32 3}
!38 = !{i32 1, !"wchar_size", i32 4}
!39 = !{i32 8, !"PIC Level", i32 2}
!40 = !{i32 7, !"PIE Level", i32 2}
!41 = !{i32 7, !"uwtable", i32 2}
!42 = !{i32 7, !"frame-pointer", i32 2}
!43 = !{!"clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)"}
!44 = distinct !DISubprogram(name: "main", scope: !2, file: !2, line: 6, type: !45, scopeLine: 6, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !24, retainedNodes: !48)
!45 = !DISubroutineType(types: !46)
!46 = !{!47}
!47 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!48 = !{}
!49 = !DILocalVariable(name: "buf", scope: !44, file: !2, line: 7, type: !50)
!50 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 512, elements: !51)
!51 = !{!52}
!52 = !DISubrange(count: 64)
!53 = !DILocation(line: 7, column: 10, scope: !44)
!54 = !DILocalVariable(name: "k", scope: !44, file: !2, line: 8, type: !55)
!55 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!56 = !DILocation(line: 8, column: 18, scope: !44)
!57 = !DILocation(line: 8, column: 22, scope: !44)
!58 = !DILocation(line: 8, column: 45, scope: !44)
!59 = !DILocalVariable(name: "p", scope: !44, file: !2, line: 9, type: !27)
!60 = !DILocation(line: 9, column: 15, scope: !44)
!61 = !DILocation(line: 9, column: 31, scope: !44)
!62 = !DILocation(line: 9, column: 37, scope: !44)
!63 = !DILocation(line: 9, column: 39, scope: !44)
!64 = !DILocation(line: 9, column: 35, scope: !44)
!65 = !DILocalVariable(name: "z", scope: !44, file: !2, line: 10, type: !28)
!66 = !DILocation(line: 10, column: 14, scope: !44)
!67 = !DILocation(line: 10, column: 19, scope: !44)
!68 = !DILocation(line: 10, column: 18, scope: !44)
!69 = !DILocation(line: 11, column: 11, scope: !44)
!70 = !DILocation(line: 12, column: 5, scope: !44)
!71 = !DILocation(line: 13, column: 5, scope: !44)
!72 = distinct !DISubprogram(name: "VERIFIER_nondet_uint", scope: !20, file: !20, line: 115, type: !73, scopeLine: 115, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !24, retainedNodes: !48)
!73 = !DISubroutineType(types: !74)
!74 = !{!55}
!75 = !DILocalVariable(name: "x", scope: !72, file: !20, line: 116, type: !55)
!76 = !DILocation(line: 116, column: 22, scope: !72)
!77 = !DILocation(line: 117, column: 9, scope: !72)
!78 = !DILocation(line: 118, column: 16, scope: !72)
!79 = !DILocation(line: 118, column: 9, scope: !72)
