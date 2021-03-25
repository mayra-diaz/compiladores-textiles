# Parser para textiles

> **Curso:** Compiladores \
> **Integrantes:**
> - [Mayra Díaz Tramontana](https://www.linkedin.com/in/mayra-d%C3%ADaz-tramontana-7018701a4/) 201910147
> - [Joaquín Elías Ramírez Gutiérrez](https://www.linkedin.com/in/joaquin-ramirezg/) 201910277
> 
> Proyecto sobre el flujo de producción de una fábrica de textiles.

## Lexer
- **TOKEN:** estructura que almacena la información necesaria para el análisis de la cadena.
Almacena su tipo, id y una descripción.
- **LEXER:** se encarga del análisis léxico en base a un string. Para que esto sea posible 
  utiliza la estructura TOKEN. Lee la cadena de entrada caracter por caracter, y dependiendo de 
  lo que encuentra añade a un vector de TOKENS un token de un terminal o un error.
  
## CFGHandler
El handler se encarga de todas las operaciones respecto a la gramática. Esta clase lee lagramática 
y la transforma para que pueda ser utilizada. Además, crea los conjuntos delos primeros y siguientes.
  
## Parser
El parser crea la tabla LL(1), haciendo uso del handler para la gramática, y la utilizapara analizar 
cadenas haciendo uso del lexer.

## Programa completo
Implementa un menú interactivo en consola para el usuario que desee información sobre el flujo de producción 
o quiera verificar un flujo determinado.
