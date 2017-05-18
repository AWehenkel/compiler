define i32 @main(){
	%1 = call %struct.Main* @MainNew()
	%2 = getelementptr inbounds %struct.Main* %1, i32 0, i32 0
	%3 = load %struct.MainVTable** %2
	%4 = getelementptr inbounds %struct.MainVTable* %3, i32 0, i32 6
	%5 = load i32 (%struct.Main*)** %4
	%6 = call i32 %5(%struct.Main* %1)
	ret i32 %6
}
