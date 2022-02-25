-module(trClient).
-import(lists, [foreach/2]).
-compile(export_all).

selectBook(Server) ->
    Server ! {self(), {selectBook}},
    receive
	    {Server,Response} ->
	    Response
    end.

selectCustomer(Server) ->
    Server ! {self(), {selectCustomer }},
    receive
	    {Server,Response} ->
	    Response
    end.

requested(Server, Cc) ->
    Server ! {self(), {requested, Cc }},
    receive
	    {Server,Response} ->
	    Response
    end.

requestedTitle(Server, Title) ->
    Server ! {self(), {requestedTitle, Title }},
    receive
	    {Server,Response} ->
	    Response
    end.

idsTitle(Server, Title) ->
    Server ! {self(), {idsTitle, Title }},
    receive
	    {Server,Response} ->
	    Response
    end.

numRequest(Server, Cc) ->
    Server ! {self(), {numRequest, Cc }},
    receive
	    {Server,Response} ->
	    Response
    end.

taken(Server, Id) ->
    Server ! {self(), {taken, Id }},
    receive
	    {Server,Response} ->
	    Response
    end.

request(Server, Cc, Id) ->
    Server ! {self(), {request, Cc, Id }},
    receive
	    {Server,Response} ->
	    Response
    end.

back(Server, Id) ->
    Server ! {self(), {back, Id }},
    receive
	    {Server,Response} ->
	    Response
    end.

add_book_item(Server, Id, Title, Creator) ->
    Server ! {self(), {add_book_item, Id, Title, Creator }},
    receive
	    {Server,Response} ->
	    Response
    end.

remove_book_item(Server, Id) ->
    Server ! {self(), {remove_book_item, Id }},
    receive
	    {Server,Response} ->
	    Response
    end.

add_customer(Server, Cc, Name, Address, Phone) ->
    Server ! {self(), {add_customer, Cc, Name, Address, Phone }},
    receive
	    {Server,Response} ->
	    Response
    end.

remove_customer(Server, Cc) ->
    Server ! {self(), {remove_customer, Cc }},
    receive
	    {Server,Response} ->
	    Response
    end.

resetTables(Server) ->
    Server ! {self(), {resetTables}},
    receive
	    {Server,Response} ->
	    Response
    end.
