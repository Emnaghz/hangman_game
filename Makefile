CFLAGS = -I.
MAIN = hangman
$(MAIN): main.c
	$(CC) $(CFLAGS) main.c -o $(MAIN) -lm

run: $(MAIN)
# clear
	./$(MAIN)
	rm -f $(MAIN)

clean:
	rm -f $(MAIN)
