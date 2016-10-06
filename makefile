$(name):$(name).cpp
	g++ -g -o $(name).exe $(name).cpp
	@echo $(name).exe is made
clean:
	rm *.exe
