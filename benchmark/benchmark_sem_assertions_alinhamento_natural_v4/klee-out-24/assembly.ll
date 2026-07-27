; ModuleID = '/work/benchmark_sem_assertions_alinhamento_natural_v4/E_uint16_t_aligned.bc'
source_filename = "/work/benchmark_sem_assertions_alinhamento_natural_v4/E_uint16_t_aligned.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [12 x i8] c"nondet_uint\00", align 1, !dbg !0

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !25 {
entry:
  %retval = alloca i32, align 4
  %buf = alloca [64 x i8], align 16
  %k = alloca i32, align 4
  %p = alloca ptr, align 8
  %z = alloca i16, align 2
  store i32 0, ptr %retval, align 4
  call void @llvm.dbg.declare(metadata ptr %buf, metadata !31, metadata !DIExpression()), !dbg !35
  call void @llvm.dbg.declare(metadata ptr %k, metadata !36, metadata !DIExpression()), !dbg !38
  %call = call i32 @VERIFIER_nondet_uint(), !dbg !39
  %rem = urem i32 %call, 6, !dbg !40
  store i32 %rem, ptr %k, align 4, !dbg !38
  call void @llvm.dbg.declare(metadata ptr %p, metadata !41, metadata !DIExpression()), !dbg !42
  %arraydecay = getelementptr inbounds [64 x i8], ptr %buf, i64 0, i64 0, !dbg !43
  %0 = load i32, ptr %k, align 4, !dbg !44
  %conv = zext i32 %0 to i64, !dbg !44
  %mul = mul i64 %conv, 2, !dbg !45
  %add.ptr = getelementptr inbounds i8, ptr %arraydecay, i64 %mul, !dbg !46
  store ptr %add.ptr, ptr %p, align 8, !dbg !42
  call void @llvm.dbg.declare(metadata ptr %z, metadata !47, metadata !DIExpression()), !dbg !48
  %1 = load ptr, ptr %p, align 8, !dbg !49
  %2 = load i16, ptr %1, align 2, !dbg !50
  store i16 %2, ptr %z, align 2, !dbg !48
  %3 = load i16, ptr %z, align 2, !dbg !51
  ret i32 0, !dbg !52
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind uwtable
define internal i32 @VERIFIER_nondet_uint() #0 !dbg !53 {
entry:
  %x = alloca i32, align 4
  call void @llvm.dbg.declare(metadata ptr %x, metadata !56, metadata !DIExpression()), !dbg !57
  call void @klee_make_symbolic(ptr noundef %x, i64 noundef 4, ptr noundef @.str), !dbg !58
  %0 = load i32, ptr %x, align 4, !dbg !59
  ret i32 %0, !dbg !60
}

declare void @klee_make_symbolic(ptr noundef, i64 noundef, ptr noundef) #2

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.dbg.cu = !{!7}
!llvm.module.flags = !{!17, !18, !19, !20, !21, !22, !23}
!llvm.ident = !{!24}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(scope: null, file: !2, line: 117, type: !3, isLocal: true, isDefinition: true)
!2 = !DIFile(filename: "/work/benchmark_sem_assertions_alinhamento_natural_v4/verifier.h", directory: "", checksumkind: CSK_MD5, checksum: "067d54c60d1b3554bee88b305f379a99")
!3 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 96, elements: !5)
!4 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!5 = !{!6}
!6 = !DISubrange(count: 12)
!7 = distinct !DICompileUnit(language: DW_LANG_C11, file: !8, producer: "clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !9, globals: !16, splitDebugInlining: false, nameTableKind: None)
!8 = !DIFile(filename: "/work/benchmark_sem_assertions_alinhamento_natural_v4/E_uint16_t_aligned.c", directory: "/home/klee", checksumkind: CSK_MD5, checksum: "f01861e94cc2940d9c2eb822c3bed50b")
!9 = !{!10}
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64)
!11 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !12, line: 25, baseType: !13)
!12 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h", directory: "", checksumkind: CSK_MD5, checksum: "2bf2ae53c58c01b1a1b9383b5195125c")
!13 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint16_t", file: !14, line: 40, baseType: !15)
!14 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "", checksumkind: CSK_MD5, checksum: "d108b5f93a74c50510d7d9bc0ab36df9")
!15 = !DIBasicType(name: "unsigned short", size: 16, encoding: DW_ATE_unsigned)
!16 = !{!0}
!17 = !{i32 7, !"Dwarf Version", i32 5}
!18 = !{i32 2, !"Debug Info Version", i32 3}
!19 = !{i32 1, !"wchar_size", i32 4}
!20 = !{i32 8, !"PIC Level", i32 2}
!21 = !{i32 7, !"PIE Level", i32 2}
!22 = !{i32 7, !"uwtable", i32 2}
!23 = !{i32 7, !"frame-pointer", i32 2}
!24 = !{!"clang version 16.0.6 (https://github.com/llvm/llvm-project.git 7cbf1a2591520c2491aa35339f227775f4d3adf6)"}
!25 = distinct !DISubprogram(name: "main", scope: !26, file: !26, line: 6, type: !27, scopeLine: 6, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !7, retainedNodes: !30)
!26 = !DIFile(filename: "/work/benchmark_sem_assertions_alinhamento_natural_v4/E_uint16_t_aligned.c", directory: "", checksumkind: CSK_MD5, checksum: "f01861e94cc2940d9c2eb822c3bed50b")
!27 = !DISubroutineType(types: !28)
!28 = !{!29}
!29 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!30 = !{}
!31 = !DILocalVariable(name: "buf", scope: !25, file: !26, line: 7, type: !32)
!32 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 512, elements: !33)
!33 = !{!34}
!34 = !DISubrange(count: 64)
!35 = !DILocation(line: 7, column: 10, scope: !25)
!36 = !DILocalVariable(name: "k", scope: !25, file: !26, line: 8, type: !37)
!37 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!38 = !DILocation(line: 8, column: 18, scope: !25)
!39 = !DILocation(line: 8, column: 22, scope: !25)
!40 = !DILocation(line: 8, column: 45, scope: !25)
!41 = !DILocalVariable(name: "p", scope: !25, file: !26, line: 9, type: !10)
!42 = !DILocation(line: 9, column: 15, scope: !25)
!43 = !DILocation(line: 9, column: 31, scope: !25)
!44 = !DILocation(line: 9, column: 37, scope: !25)
!45 = !DILocation(line: 9, column: 39, scope: !25)
!46 = !DILocation(line: 9, column: 35, scope: !25)
!47 = !DILocalVariable(name: "z", scope: !25, file: !26, line: 10, type: !11)
!48 = !DILocation(line: 10, column: 14, scope: !25)
!49 = !DILocation(line: 10, column: 19, scope: !25)
!50 = !DILocation(line: 10, column: 18, scope: !25)
!51 = !DILocation(line: 11, column: 11, scope: !25)
!52 = !DILocation(line: 12, column: 5, scope: !25)
!53 = distinct !DISubprogram(name: "VERIFIER_nondet_uint", scope: !2, file: !2, line: 115, type: !54, scopeLine: 115, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !7, retainedNodes: !30)
!54 = !DISubroutineType(types: !55)
!55 = !{!37}
!56 = !DILocalVariable(name: "x", scope: !53, file: !2, line: 116, type: !37)
!57 = !DILocation(line: 116, column: 22, scope: !53)
!58 = !DILocation(line: 117, column: 9, scope: !53)
!59 = !DILocation(line: 118, column: 16, scope: !53)
!60 = !DILocation(line: 118, column: 9, scope: !53)
