compile:
	gcc QuestãoThreads.c -o QuestãoThreads -pthread
	
run:
	./QuestãoThreads
	
clean: 
	rm -rf *.o QuestãoThreads
