CC := g++
target := barrier
${target} : $(wildcard *.cpp)
	$(CC) $^ --std=c++11 -stdlib=libc++ -lpthread -o $@

.PHONY: clean
clean:
	rm -rf $(target)
