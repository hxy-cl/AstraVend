vin : admin.o customer.o inventory.o llist.o main.o product.o storage.o transaction.o
	gcc -o $@ $^
clean :
	rm -rf *.o *.dat vin
