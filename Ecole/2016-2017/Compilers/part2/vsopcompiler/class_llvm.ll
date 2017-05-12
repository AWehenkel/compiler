; ModuleID = 'class_llvm.c'
target datalayout = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i686-pc-linux-gnu"

%struct.Child = type { %struct.ChildVTable*, i32, i32, i32 }
%struct.ChildVTable = type { {}*, {}*, void (%struct.Child*, i32)* }
%struct.Parent = type { i8 }

@ChildVTable_inst = global { void (%struct.Child*)*, void (%struct.Child*)*, void (%struct.Child*, i32)* } { void (%struct.Child*)* bitcast (void (%struct.Parent*)* @Parent_inheritedMethod to void (%struct.Child*)*), void (%struct.Child*)* @Child_overriddenMethod, void (%struct.Child*, i32)* @Child_newMethod }, align 4
@.str = private unnamed_addr constant [5 x i8] c"self\00", align 1
@.str.1 = private unnamed_addr constant [13 x i8] c"class_llvm.c\00", align 1
@__PRETTY_FUNCTION__.Child_new = private unnamed_addr constant [26 x i8] c"struct Child *Child_new()\00", align 1

; Function Attrs: nounwind
define void @Parent_init(%struct.Parent* %self) #0 {
  %1 = alloca %struct.Parent*, align 4
  store %struct.Parent* %self, %struct.Parent** %1, align 4
  ret void
}

; Function Attrs: nounwind
define void @Parent_inheritedMethod(%struct.Parent* %p) #0 {
  %1 = alloca %struct.Parent*, align 4
  store %struct.Parent* %p, %struct.Parent** %1, align 4
  ret void
}

; Function Attrs: nounwind
define void @Child_overriddenMethod(%struct.Child* %c) #0 {
  %1 = alloca %struct.Child*, align 4
  store %struct.Child* %c, %struct.Child** %1, align 4
  ret void
}

; Function Attrs: nounwind
define void @Child_newMethod(%struct.Child* %c, i32 %a) #0 {
  %1 = alloca %struct.Child*, align 4
  %2 = alloca i32, align 4
  store %struct.Child* %c, %struct.Child** %1, align 4
  store i32 %a, i32* %2, align 4
  ret void
}

; Function Attrs: nounwind
define void @Child_init(%struct.Child* %self) #0 {
  %1 = alloca %struct.Child*, align 4
  %test = alloca [18 x i8], align 1
  store %struct.Child* %self, %struct.Child** %1, align 4
  %2 = load %struct.Child*, %struct.Child** %1, align 4
  %3 = bitcast %struct.Child* %2 to %struct.Parent*
  call void @Parent_init(%struct.Parent* %3)
  %4 = load %struct.Child*, %struct.Child** %1, align 4
  %5 = getelementptr inbounds %struct.Child, %struct.Child* %4, i32 0, i32 2
  store i32 0, i32* %5, align 4
  %6 = load %struct.Child*, %struct.Child** %1, align 4
  %7 = getelementptr inbounds %struct.Child, %struct.Child* %6, i32 0, i32 0
  store %struct.ChildVTable* bitcast ({ void (%struct.Child*)*, void (%struct.Child*)*, void (%struct.Child*, i32)* }* @ChildVTable_inst to %struct.ChildVTable*), %struct.ChildVTable** %7, align 4
  %8 = getelementptr inbounds [18 x i8], [18 x i8]* %test, i32 0, i32 3
  store i8 99, i8* %8, align 1
  ret void
}

; Function Attrs: nounwind
define %struct.Child* @Child_new() #0 {
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
  call void @__assert_fail(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.1, i32 0, i32 0), i32 52, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @__PRETTY_FUNCTION__.Child_new, i32 0, i32 0)) #3
  unreachable
                                                  ; No predecessors!
  br label %8

; <label>:8                                       ; preds = %7, %5
  %9 = load %struct.Child*, %struct.Child** %self, align 4
  call void @Child_init(%struct.Child* %9)
  %10 = load %struct.Child*, %struct.Child** %self, align 4
  ret %struct.Child* %10
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i32) #0

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #1

; Function Attrs: nounwind
define i32 @main() #0 {
  %myObject = alloca %struct.Child*, align 4
  %1 = call %struct.Child* @Child_new()
  store %struct.Child* %1, %struct.Child** %myObject, align 4
  %2 = load %struct.Child*, %struct.Child** %myObject, align 4
  %3 = getelementptr inbounds %struct.Child, %struct.Child* %2, i32 0, i32 0
  %4 = load %struct.ChildVTable*, %struct.ChildVTable** %3, align 4
  %5 = getelementptr inbounds %struct.ChildVTable, %struct.ChildVTable* %4, i32 0, i32 2
  %6 = load void (%struct.Child*, i32)*, void (%struct.Child*, i32)** %5, align 4
  %7 = load %struct.Child*, %struct.Child** %myObject, align 4
  call void %6(%struct.Child* %7, i32 42)
  ret i32 0
}

attributes #0 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind }
attributes #3 = { noreturn nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)"}
