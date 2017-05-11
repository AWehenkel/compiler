; ModuleID = 'class_llvm.c'
<<<<<<< HEAD
source_filename = "class_llvm.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.12.0"
=======
target datalayout = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i686-pc-linux-gnu"
>>>>>>> 818c33827eaa7881dfeb3236392a02e1a1eca3f0

%struct.Child = type { %struct.ChildVTable*, i32, i32, i32 }
%struct.ChildVTable = type { {}*, {}*, {}* }
%struct.Parent = type { i8 }

<<<<<<< HEAD
@ChildVTable_inst = global { void (%struct.Child*)*, void (%struct.Child*)*, void (%struct.Child*)* } { void (%struct.Child*)* bitcast (void (%struct.Parent*)* @Parent_inheritedMethod to void (%struct.Child*)*), void (%struct.Child*)* @Child_overriddenMethod, void (%struct.Child*)* @Child_newMethod }, align 8
@__func__.Child_new = private unnamed_addr constant [10 x i8] c"Child_new\00", align 1
@.str = private unnamed_addr constant [13 x i8] c"class_llvm.c\00", align 1
@.str.1 = private unnamed_addr constant [5 x i8] c"self\00", align 1
=======
@ChildVTable_inst = global { void (%struct.Child*)*, void (%struct.Child*)*, void (%struct.Child*)* } { void (%struct.Child*)* bitcast (void (%struct.Parent*)* @Parent_inheritedMethod to void (%struct.Child*)*), void (%struct.Child*)* @Child_overriddenMethod, void (%struct.Child*)* @Child_newMethod }, align 4
@.str = private unnamed_addr constant [5 x i8] c"self\00", align 1
@.str.1 = private unnamed_addr constant [13 x i8] c"class_llvm.c\00", align 1
@__PRETTY_FUNCTION__.Child_new = private unnamed_addr constant [26 x i8] c"struct Child *Child_new()\00", align 1
>>>>>>> 818c33827eaa7881dfeb3236392a02e1a1eca3f0

; Function Attrs: nounwind ssp uwtable
define void @Parent_init(%struct.Parent*) #0 {
  %2 = alloca %struct.Parent*, align 8
  store %struct.Parent* %0, %struct.Parent** %2, align 8
  ret void
}

; Function Attrs: nounwind ssp uwtable
define void @Parent_inheritedMethod(%struct.Parent*) #0 {
  %2 = alloca %struct.Parent*, align 8
  store %struct.Parent* %0, %struct.Parent** %2, align 8
  ret void
}

; Function Attrs: nounwind ssp uwtable
define void @Child_overriddenMethod(%struct.Child*) #0 {
  %2 = alloca %struct.Child*, align 8
  store %struct.Child* %0, %struct.Child** %2, align 8
  ret void
}

; Function Attrs: nounwind ssp uwtable
define void @Child_newMethod(%struct.Child*) #0 {
  %2 = alloca %struct.Child*, align 8
  store %struct.Child* %0, %struct.Child** %2, align 8
  ret void
}

<<<<<<< HEAD
; Function Attrs: nounwind ssp uwtable
define void @Child_init(%struct.Child*) #0 {
  %2 = alloca %struct.Child*, align 8
  %3 = alloca [18 x i8], align 16
  store %struct.Child* %0, %struct.Child** %2, align 8
  %4 = load %struct.Child*, %struct.Child** %2, align 8
  %5 = bitcast %struct.Child* %4 to %struct.Parent*
  call void @Parent_init(%struct.Parent* %5)
  %6 = load %struct.Child*, %struct.Child** %2, align 8
  %7 = getelementptr inbounds %struct.Child, %struct.Child* %6, i32 0, i32 2
  store i32 0, i32* %7, align 4
  %8 = load %struct.Child*, %struct.Child** %2, align 8
  %9 = getelementptr inbounds %struct.Child, %struct.Child* %8, i32 0, i32 0
  store %struct.ChildVTable* bitcast ({ void (%struct.Child*)*, void (%struct.Child*)*, void (%struct.Child*)* }* @ChildVTable_inst to %struct.ChildVTable*), %struct.ChildVTable** %9, align 8
  %10 = getelementptr inbounds [18 x i8], [18 x i8]* %3, i64 0, i64 3
  store i8 99, i8* %10, align 1
=======
; Function Attrs: nounwind
define void @Child_init(%struct.Child* %self) #0 {
  %1 = alloca %struct.Child*, align 4
  store %struct.Child* %self, %struct.Child** %1, align 4
  %2 = load %struct.Child*, %struct.Child** %1, align 4
  %3 = bitcast %struct.Child* %2 to %struct.Parent*
  call void @Parent_init(%struct.Parent* %3)
  %4 = load %struct.Child*, %struct.Child** %1, align 4
  %5 = getelementptr inbounds %struct.Child, %struct.Child* %4, i32 0, i32 2
  store i32 0, i32* %5, align 4
  %6 = load %struct.Child*, %struct.Child** %1, align 4
  %7 = getelementptr inbounds %struct.Child, %struct.Child* %6, i32 0, i32 0
  store %struct.ChildVTable* bitcast ({ void (%struct.Child*)*, void (%struct.Child*)*, void (%struct.Child*)* }* @ChildVTable_inst to %struct.ChildVTable*), %struct.ChildVTable** %7, align 4
>>>>>>> 818c33827eaa7881dfeb3236392a02e1a1eca3f0
  ret void
}

; Function Attrs: nounwind ssp uwtable
define %struct.Child* @Child_new() #0 {
<<<<<<< HEAD
  %1 = alloca %struct.Child*, align 8
  %2 = call i8* @malloc(i64 16)
  %3 = bitcast i8* %2 to %struct.Child*
  store %struct.Child* %3, %struct.Child** %1, align 8
  %4 = load %struct.Child*, %struct.Child** %1, align 8
  %5 = icmp ne %struct.Child* %4, null
  %6 = xor i1 %5, true
  %7 = zext i1 %6 to i32
  %8 = sext i32 %7 to i64
  %9 = icmp ne i64 %8, 0
  br i1 %9, label %10, label %12

; <label>:10                                      ; preds = %0
  call void @__assert_rtn(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @__func__.Child_new, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str, i32 0, i32 0), i32 50, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.1, i32 0, i32 0)) #3
=======
  %i = alloca i32, align 4
  %self = alloca %struct.Child*, align 4
  store i32 1, i32* %i, align 4
  %1 = call noalias i8* @malloc(i32 16) #2
  %2 = bitcast i8* %1 to %struct.Child*
  store %struct.Child* %2, %struct.Child** %self, align 4
  %3 = load %struct.Child*, %struct.Child** %self, align 4
  %4 = icmp ne %struct.Child* %3, null
  br i1 %4, label %5, label %6

; <label>:5                                       ; preds = %0
  br label %8

; <label>:6                                       ; preds = %0
  call void @__assert_fail(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.1, i32 0, i32 0), i32 50, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @__PRETTY_FUNCTION__.Child_new, i32 0, i32 0)) #3
>>>>>>> 818c33827eaa7881dfeb3236392a02e1a1eca3f0
  unreachable
                                                  ; No predecessors!
  br label %13

<<<<<<< HEAD
; <label>:12                                      ; preds = %0
  br label %13

; <label>:13                                      ; preds = %12, %11
  %14 = load %struct.Child*, %struct.Child** %1, align 8
  call void @Child_init(%struct.Child* %14)
  %15 = load %struct.Child*, %struct.Child** %1, align 8
  ret %struct.Child* %15
=======
; <label>:8                                       ; preds = %7, %5
  %9 = load %struct.Child*, %struct.Child** %self, align 4
  call void @Child_init(%struct.Child* %9)
  %10 = load %struct.Child*, %struct.Child** %self, align 4
  ret %struct.Child* %10
>>>>>>> 818c33827eaa7881dfeb3236392a02e1a1eca3f0
}

declare i8* @malloc(i64) #1

; Function Attrs: noreturn
declare void @__assert_rtn(i8*, i8*, i32, i8*) #2

; Function Attrs: nounwind ssp uwtable
define i32 @main() #0 {
  %1 = alloca %struct.Child, align 8
  ret i32 0
}

<<<<<<< HEAD
attributes #0 = { nounwind ssp uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+sse4.1,+ssse3" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+sse4.1,+ssse3" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { noreturn "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+sse4.1,+ssse3" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn }
=======
attributes #0 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind }
attributes #3 = { noreturn nounwind }
>>>>>>> 818c33827eaa7881dfeb3236392a02e1a1eca3f0

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

<<<<<<< HEAD
!0 = !{i32 1, !"PIC Level", i32 2}
!1 = !{!"Apple LLVM version 8.0.0 (clang-800.0.42.1)"}
=======
!0 = !{!"clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)"}
>>>>>>> 818c33827eaa7881dfeb3236392a02e1a1eca3f0
