-module(trServer).
-import(lists, [foreach/2]).
-compile(export_all).

-include_lib("stdlib/include/qlc.hrl").

-record(customer, {cc, name, address, phone}).
-record(book, {id, title, creator}).
-record(taken, {id, cc}).



do_this_once() ->
	mnesia:create_schema([node()]),
	mnesia:start(),
	mnesia:create_table(customer,  [{attributes, record_info(fields, customer)}]),
    mnesia:create_table(book,   [{attributes, record_info(fields, book)}]),
    mnesia:create_table(taken,   [{attributes, record_info(fields, taken)}]),
    mnesia:stop().

start() ->
    mnesia:start(),
    mnesia:wait_for_tables([customer,book, taken], 20000),
    spawn(trServer,loop,[]).
    %%
loop() ->
	receive 
		{Client, {selectBook}} ->
			Client ! {self(), demo(selectBook)},
			loop();
		{Client, {selectCustomer}} ->
			Client ! {self(), demo(selectCustomer)},
			loop();
		{Client, {requested,Cc}} ->
			Client ! {self(), demo(requested, Cc)},
			loop();
		{Client, {requestedTitle,Title}} ->
			Client ! {self(), demo(requestedTitle, Title)},
			loop();
		{Client, {idsTitle,Title}} ->
			Client ! {self(), demo(idsTitle, Title)},
			loop();
		{Client, {numRequest,Cc}} ->
			Client ! {self(), numRequest(Cc)},
			loop();
		{Client, {taken,Id}} ->
			Client ! {self(), taken(Id)},
			loop();
		{Client, {request,Cc, Id}}->
			Client ! {self(), request(Cc, Id)},
			loop();
		{Client, {back, Id}} ->
			Client ! {self(), back( Id)},
			loop();
		{Client, {add_book_item,Id, Title, Creator} }->
			Client ! {self(), add_book_item(Id, Title, Creator)},
			loop();
		{Client, {remove_book_item,Id}} ->
			Client ! {self(), remove_book_item(Id)},
			loop();
		{Client, {add_customer,Cc, Name, Address, Phone}} ->
			Client ! {self(), add_customer(Cc, Name, Address, Phone)},
			loop();
		{Client, {resetTables}} ->
			Client ! {self(), reset_tables()},
			loop();
		{Client, {remove_customer,Cc}} ->
			Client ! {self(), remove_customer(Cc)},
			loop();
        {Client, Other} ->
            Client ! {self(), {Other, error}},
            loop()
	end.

demo(selectBook) ->
    do(qlc:q([X || X <- mnesia:table(book)]));

demo(selectCustomer) ->
    do(qlc:q([X || X <- mnesia:table(customer)])).

demo(requested, Cc) ->
    do(qlc:q([X#book.title || X <- mnesia:table(book),
                Y <- mnesia:table(taken),
                Y#taken.cc == Cc,
                Y#taken.id =:= X#book.id 
                ]));

demo(book, Id) ->
    do(qlc:q([X#book.id || X <- mnesia:table(book),
                X#book.id == Id
                ]));

demo(person, Cc) ->
    do(qlc:q([X#customer.cc || X <- mnesia:table(book),
                X#customer.cc == Cc
                ]));

demo(isTaken, Id) ->
    do(qlc:q([X#taken.id || X <- mnesia:table(taken),
                X#taken.id == Id
                ]));

demo(requestedTitle, Title) ->
    do(qlc:q([X#customer.name || X <- mnesia:table(customer),
                 Y <- mnesia:table(taken),
                 W <- mnesia:table(book),
                 W#book.title == Title,
                 X#customer.cc =:= Y#taken.cc,
                 W#book.id =:= Y#taken.id
                ]));


demo(idsTitle, Title) ->
    do(qlc:q([X#book.id || X <- mnesia:table(book),
        X#book.title == Title
        ])).

numRequest(Cc) ->
    L = demo(requested, Cc),
    io:format("~p~n", [length(L)]).

taken(Id) -> 
    F = fun() ->
        L = demo(isTaken,Id),
        if 
            length(L) == 1 ->           
            io:format("True~n");
            true ->
            io:format("False~n")
        end
    end,
    mnesia:transaction(F).

request(Cc,Id) ->
    Row = #taken{id=Id,cc=Cc},
    F = fun() ->
        L1 = demo(person,Cc),
        L2 = demo(book,Id),
        if length(L1) == 1 ->
            if length(L2) == 1 ->
                mnesia:write(Row);
                true ->
                mnesia:abort(taken)
            end;
            true ->
            mnesia:abort(taken)
        end
    end,
    mnesia:transaction(F).
    
back(Id) ->
    Oid = {taken, Id},
    F = fun() ->
        mnesia:delete(Oid)
    end,
    mnesia:transaction(F).

do(Q) ->
    F = fun() -> qlc:e(Q) end,
    {atomic, Val} = mnesia:transaction(F),
    Val.

add_book_item(Id, Title, Creator) ->
    Row = #book{id=Id, title=Title, creator=Creator},
    F = fun() ->
        L = demo(book,Id),
        if length(L) == 0 ->
		    mnesia:write(Row);
            true ->
            mnesia:abort(book)
        end
	end,
    mnesia:transaction(F).

remove_book_item(Id) ->
    Oid = {book, Id},
    Oid1 = {taken, Id},
    F = fun() ->
        mnesia:delete(Oid),
        mnesia:delete(Oid1)
    end,
    mnesia:transaction(F).

add_customer(Cc, Name, Address,Phone) ->
    Row = #customer{cc=Cc, name=Name, address=Address, phone=Phone},
    F = fun() ->
        L = demo(person,Cc),
        if length(L) == 0 ->
            mnesia:write(Row);
            true ->
            mnesia:abort(customer)
        end
    end,
    mnesia:transaction(F).

remove_customer(Cc) ->
    Oid = {book, Cc},
    Oid1 = {taken, Cc},
    F = fun() ->
        mnesia:delete(Oid),
        mnesia:delete(Oid1)
    end,
    mnesia:transaction(F).

example_tables() ->
    [
     {book,1, 1984, george_orwell},
     {book,2, name_of_the_wind, patrick_rothfuss},
     {book,3, the_way_of_kings, brandon_sanderson},
     {book,4, the_final_empire, brandon_sanderson},
     {book,5, the_final_empire, brandon_sanderson},
     {customer,1, joao, rua_dos_amores, 123},
     {customer,2, maria, rua_dos_amores,122},
     {customer, 3,paulo,rua_do_porto,222},
     {taken,1, 1},
     {taken,2, 1},
     {taken,3, 2}
    ].

reset_tables() ->
    mnesia:clear_table(book),
    mnesia:clear_table(customer),
    mnesia:clear_table(taken),
    F = fun() ->
            foreach(fun mnesia:write/1, example_tables())
      end,
    mnesia:transaction(F).