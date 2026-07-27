; ModuleID = '/work/benchmark_com_assertions_com_alinhamento_explicito_v4/D_uint32_t_misaligned.bc'
source_filename = "/work/benchmark_com_assertions_com_alinhamento_explicito_v4/D_uint32_t_misaligned.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.S = type { i8, i32 }

@.str = private unnamed_addr constant [37 x i8] c"((uintptr_t)(p) % sizeof(*(p))) == 0\00", align 1, !dbg !0
@.str.1 = private unnamed_addr constant [84 x i8] c"/work/benchmark_com_assertions_com_alinhamento_explicito_v4/D_uint32_t_misaligned.c\00", align 1, !dbg !7
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [15 x i8] c"int main(void)\00", align 1, !dbg !12

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !40 {
entry:
  %retval = alloca i32, align 4
  %s = alloca %struct.S, align 4
  %base = alloca ptr, align 8
  %p = alloca ptr, align 8
  %z = alloca i32, align 4
  store i32 0, ptr %retval, align 4
  call void @llvm.dbg.declare(metadata ptr %s, metadata !45, metadata !DIExpression()), !dbg !50
  call void @llvm.dbg.declare(metadata ptr %base, metadata !51, metadata !DIExpression()), !dbg !52
  store ptr %s, ptr %base, align 8, !dbg !52
  call void @llvm.dbg.declare(metadata ptr %p, metadata !53, metadata !DIExpression()), !dbg !54
  %0 = load ptr, ptr %base, align 8, !dbg !55
  %add.ptr = getelementptr inbounds i8, ptr %0, i64 1, !dbg !56
  store ptr %add.ptr, ptr %p, align 8, !dbg !54
  call void @llvm.dbg.declare(metadata ptr %z, metadata !57, metadata !DIExpression()), !dbg !58
  %1 = load ptr, ptr %p, align 8, !dbg !59
  %2 = load i32, ptr %1, align 4, !dbg !60
  store i32 %2, ptr %z, align 4, !dbg !58
  %3 = load i32, ptr %z, align 4, !dbg !61
  %4 = load ptr, ptr %p, align 8, !dbg !62
  %5 = ptrtoint ptr %4 to i64, !dbg !62
  %rem = urem i64 %5, 4, !dbg !62
  %cmp = icmp eq i64 %rem, 0, !dbg !62
  br i1 %cmp, label %cond.end, label %cond.false, !dbg !62

cond.false:                                       ; preds = %entry
  call void @__assert_fail(ptr noundef @.str, ptr noundef @.str.1, i32 noundef 18, ptr noundef @__PRETTY_FUNCTION__.main) #3, !dbg !62
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
!llvm.module.flags = !{!32, !33, !34, !35, !36, !37, !38}
!llvm.ident = !{!39}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(scope: null, file: !2, line: 18, type: !3, isLocal: true, isDefinition: true)
!2 = !DIFile(filename: "/work/benchmark_com_assertions_com_alinhamento_explicito_v4/D_uint32_t_misaligned.c", directory: "", checksumkind: CSK_MD5, checksum: "244a86426d42faae54014fdba7ef0665")
!3 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 296, elements: !5)
!4 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!5 = !{!6}
!6 = !DISubrange(count: 37)
!7 = !DIGlobalVariableExpression(var: !8, expr: !DIExpression())
!8 = distinct !DIGlobalVariable(scope: null, file: !2, line: 18, type: !9, isLocal: true, isDefinition: true)
!9 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 672, elements: !10)
!10 = !{!11}
!11 = !DISubrange(count: 84)
!12 = !DIGlobalVariableExpression(var: !13, expr: !DIExpression())
!13 = distinct !DIGlobalVariable(scope: null, file: !2, line: 18, type: !14, isLocal: true, isDefinition: true)
!14 = !DICompositeType(tag: DW_TAG_array_type, baseType: !15, size: 120, elements: !16)
!15 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !4)
!16 = !{!17}
!17 = !DISubrange(count: 15)
!18 = distinct !DICompileUnit(language: DW_LANG_C11, file: !19, producer: "clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !20, globals: !31, splitDebugInlining: false, nameTableKind: None)
!19 = !DIFile(filename: "/work/benchmark_com_assertions_com_alinhamento_explicito_v4/D_uint32_t_misaligned.c", directory: "/home/klee", checksumkind: CSK_MD5, checksum: "244a86426d42faae54014fdba7ef0665")
!20 = !{!21, !22, !28}
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64)
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64)
!23 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !24, line: 26, baseType: !25)
!24 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h", directory: "", checksumkind: CSK_MD5, checksum: "2bf2ae53c58c01b1a1b9383b5195125c")
!25 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint32_t", file: !26, line: 42, baseType: !27)
!26 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "", checksumkind: CSK_MD5, checksum: "d108b5f93a74c50510d7d9bc0ab36df9")
!27 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
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
!40 = distinct !DISubprogram(name: "main", scope: !2, file: !2, line: 10, type: !41, scopeLine: 10, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !18, retainedNodes: !44)
!41 = !DISubroutineType(types: !42)
!42 = !{!43}
!43 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!44 = !{}
!45 = !DILocalVariable(name: "s", scope: !40, file: !2, line: 11, type: !46, align: 32)
!46 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "S", file: !2, line: 5, size: 64, elements: !47)
!47 = !{!48, !49}
!48 = !DIDerivedType(tag: DW_TAG_member, name: "a", scope: !46, file: !2, line: 6, baseType: !4, size: 8)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "b", scope: !46, file: !2, line: 7, baseType: !23, size: 32, offset: 32)
!50 = !DILocation(line: 11, column: 33, scope: !40)
!51 = !DILocalVariable(name: "base", scope: !40, file: !2, line: 12, type: !21)
!52 = !DILocation(line: 12, column: 11, scope: !40)
!53 = !DILocalVariable(name: "p", scope: !40, file: !2, line: 15, type: !22)
!54 = !DILocation(line: 15, column: 15, scope: !40)
!55 = !DILocation(line: 15, column: 31, scope: !40)
!56 = !DILocation(line: 15, column: 36, scope: !40)
!57 = !DILocalVariable(name: "z", scope: !40, file: !2, line: 16, type: !23)
!58 = !DILocation(line: 16, column: 14, scope: !40)
!59 = !DILocation(line: 16, column: 19, scope: !40)
!60 = !DILocation(line: 16, column: 18, scope: !40)
!61 = !DILocation(line: 17, column: 11, scope: !40)
!62 = !DILocation(line: 18, column: 5, scope: !40)
!63 = !DILocation(line: 19, column: 5, scope: !40)
