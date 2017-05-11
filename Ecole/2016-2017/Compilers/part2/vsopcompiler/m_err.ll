; ModuleID = 'm_err.c'
target datalayout = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i686-pc-linux-gnu"

; Function Attrs: nounwind
define i32 @lol(i32 %a) #0 {
  %1 = alloca i32, align 4
  store i32 %a, i32* %1, align 4
  ret i32 1
}

; Function Attrs: nounwind
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %a = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 @lol(i32 1)
  store i32 %2, i32* %a, align 4
  br label %3

; <label>:3                                       ; preds = %6, %0
  %4 = load i32, i32* %a, align 4
  %5 = icmp sgt i32 %4, 0
  br i1 %5, label %6, label %9

; <label>:6                                       ; preds = %3
  %7 = load i32, i32* %a, align 4
  %8 = add nsw i32 %7, -1
  store i32 %8, i32* %a, align 4
  br label %3

; <label>:9                                       ; preds = %3
  ret i32 0
}

attributes #0 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)"}
