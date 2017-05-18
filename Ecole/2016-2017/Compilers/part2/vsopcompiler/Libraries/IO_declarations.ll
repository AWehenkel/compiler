declare i1 @inputBool()
declare i32 @inputInt32()
declare i8* @inputLine()
declare void @print(i8*)
declare void @printInt32(i32)
declare void @printBool(i1)
declare i32 @strcmp(i8*, i8*)
declare float @llvm.powi.f32(float, i32)

@.str_empty = private unnamed_addr constant [1 x i8] c"\00", align 1
