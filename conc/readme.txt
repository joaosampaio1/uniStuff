UP201805112 JOÃO SAMPAIO

--------------------------------------------

Para iniciar o server (trServer) é necessario correr a funçao do_this_once() e start(), funçoes basicas para o inicar, sendo o start para começar o loop principal que chama as funçoes de request.

--------------------------------------------

no cliente (trClient) existem as funçoes

resetTables() - deve ser utilizado para criar data nas tabelas (dá reset na tabela, para a data default)



selectBook(Server) - dá a lista com todos os livros e os atributos de cada livro

selectCustomer(Server) - dá a lista com todos os clientes e os atributos de cada cliente

requested(Server,Cc) - retorna uma lista de todos os livros emprestados ao cliente associado ao "Cc"

requestedTitle(Server,Title) - retorna todos os clientes que tem emprestado o livro com o titulo "Title"

idsTitle(Server,Title) - retorna todos os ids com o titulo "Title"

numRequest(Server,Cc) - retorna o numero de livros emprestado ao cliente associado ao numero "Cc"

taken(Server, Id) - retorna true caso o livro "Id" esteje emprestado

request(Server, Cc, Id) - empresta o livro "Id" ao cliente "Cc" (é colocado na tabela taken a informação)

back(Server,Id) - devolve o livro "Id" (remove da tabela taken o livro associado ao "Id")

add_book_item(Server, Id, Title, Creator) - adiciona um livro á tabela book com os atributos, o Id tem de ser unico

remove_book_item(Id) - remove o livro da tabela book associado ao "Id" e o livro (se tiver emprestado) da tabela taken, ou seja o livro deixa de estar emprestado

add_customer(Server, Cc, Name, Address, Phone) - adiciona o cliente á tabela customer com os atributos, o Cc tem de ser unico

remove_customer(Cc) -remove o cliente da tabela customer associado ao "Cc" e todos os livros que ele tiver da tabela taken, ou seja os livros deixam de estar emprestados


Notas:
o programa tem estes 2 warning, acho que nao sao relevantes

-trServer.erl:104: Warning: cannot handle more than one join efficiently
-trServer.erl:3: Warning: export_all flag enabled - all functions will be exported

o trServer tem 3 funçoes auxiliares demo(person), demo(book), demo(isTaken) para ajudar as funçoes principais
