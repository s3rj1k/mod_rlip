APXS=/usr/bin/apxs2

mod_rlip.so: mod_rlip.c
	$(APXS) -c -n $@ mod_rlip.c

mod_rlip.c:

install: mod_rlip.so
	$(APXS) -i -S LIBEXECDIR=$(DESTDIR)$$($(APXS) -q LIBEXECDIR)/ -n mod_rlip.so mod_rlip.la

clean:
	rm -rf *~ *.o *.so *.lo *.la *.slo *.loT .libs/
