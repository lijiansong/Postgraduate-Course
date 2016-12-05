; ModuleID = 'test.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @foo(i32 %flag) #0 {
  %1 = alloca i32, align 4
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  %z = alloca i32, align 4
  store i32 %flag, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32* %1, metadata !11, metadata !12), !dbg !13
  call void @llvm.dbg.declare(metadata i32* %x, metadata !14, metadata !12), !dbg !15
  store i32 10, i32* %x, align 4, !dbg !15
  call void @llvm.dbg.declare(metadata i32* %y, metadata !16, metadata !12), !dbg !17
  store i32 10, i32* %y, align 4, !dbg !17
  call void @llvm.dbg.declare(metadata i32* %z, metadata !18, metadata !12), !dbg !19
  %2 = load i32, i32* %1, align 4, !dbg !20
  %3 = icmp ne i32 %2, 0, !dbg !20
  br i1 %3, label %4, label %6, !dbg !22

; <label>:4                                       ; preds = %0
  %5 = load i32, i32* %x, align 4, !dbg !23
  store i32 %5, i32* %z, align 4, !dbg !25
  br label %8, !dbg !26

; <label>:6                                       ; preds = %0
  %7 = load i32, i32* %y, align 4, !dbg !27
  store i32 %7, i32* %z, align 4, !dbg !29
  br label %8

; <label>:8                                       ; preds = %6, %4
  %9 = load i32, i32* %x, align 4, !dbg !30
  %10 = load i32, i32* %y, align 4, !dbg !31
  %11 = add nsw i32 %9, %10, !dbg !32
  ret i32 %11, !dbg !33
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!8, !9}
!llvm.ident = !{!10}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.7.0 (tags/RELEASE_370/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "test.c", directory: "/home/lianli/work/llvm-3.7/tools/llvm-assignment")
!2 = !{}
!3 = !{!4}
!4 = !DISubprogram(name: "foo", scope: !1, file: !1, line: 1, type: !5, isLocal: false, isDefinition: true, scopeLine: 1, flags: DIFlagPrototyped, isOptimized: false, function: i32 (i32)* @foo, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !7}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !{i32 2, !"Dwarf Version", i32 4}
!9 = !{i32 2, !"Debug Info Version", i32 3}
!10 = !{!"clang version 3.7.0 (tags/RELEASE_370/final)"}
!11 = !DILocalVariable(tag: DW_TAG_arg_variable, name: "flag", arg: 1, scope: !4, file: !1, line: 1, type: !7)
!12 = !DIExpression()
!13 = !DILocation(line: 1, column: 13, scope: !4)
!14 = !DILocalVariable(tag: DW_TAG_auto_variable, name: "x", scope: !4, file: !1, line: 2, type: !7)
!15 = !DILocation(line: 2, column: 8, scope: !4)
!16 = !DILocalVariable(tag: DW_TAG_auto_variable, name: "y", scope: !4, file: !1, line: 3, type: !7)
!17 = !DILocation(line: 3, column: 8, scope: !4)
!18 = !DILocalVariable(tag: DW_TAG_auto_variable, name: "z", scope: !4, file: !1, line: 4, type: !7)
!19 = !DILocation(line: 4, column: 8, scope: !4)
!20 = !DILocation(line: 6, column: 8, scope: !21)
!21 = distinct !DILexicalBlock(scope: !4, file: !1, line: 6, column: 8)
!22 = !DILocation(line: 6, column: 8, scope: !4)
!23 = !DILocation(line: 7, column: 11, scope: !24)
!24 = distinct !DILexicalBlock(scope: !21, file: !1, line: 6, column: 14)
!25 = !DILocation(line: 7, column: 9, scope: !24)
!26 = !DILocation(line: 8, column: 4, scope: !24)
!27 = !DILocation(line: 9, column: 11, scope: !28)
!28 = distinct !DILexicalBlock(scope: !21, file: !1, line: 8, column: 11)
!29 = !DILocation(line: 9, column: 9, scope: !28)
!30 = !DILocation(line: 12, column: 11, scope: !4)
!31 = !DILocation(line: 12, column: 15, scope: !4)
!32 = !DILocation(line: 12, column: 13, scope: !4)
!33 = !DILocation(line: 12, column: 4, scope: !4)
