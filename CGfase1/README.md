# Como executar
No terminal escrever __make__ e a makefile vai gerar os ficheiros _.3d_ com as seguintes propriedades:
  - __plane:__
      ```
      comprimento        = 4
      nome do ficheiro   = plane.3d
      ```

  - __box:__
      ```
      tamanho x          = 2
      tamanho y          = 2
      tamanho z          = 2
      número de divisões = 3
      nome do ficheiro   = box.3d
      ```

  - __sphere:__
      ```
      raio               = 2
      fatias             = 50
      camadas            = 50
      nome do ficheiro   = sphere.3d
      ```

  - __cone:__
      ```
      raio da base       = 2
      altura             = 2
      fatias             = 50
      camadas            = 50
      nome do ficheiro   = cone.3d
      ```

De seguida é executado o motor com o argumento "__configuracao.xml__", que contém esta informação:

    <scene>
      <model file="plane.3d" />
      <model file="cone.3d" />
      <model file="sphere.3d" />
      <model file="box.3d" />
    </scene>

___
# Gerador
- Os ficheiros _.3d_ são gerados na pasta principal do motor
- __Argumentos__:
    - __plane__:
        - Comprimento
        - Nome do ficheiro para guardar
    - __box__:
        - Tamanho X
        - Tamanho Y
        - Tamanho Z
        - Número de divisões (opcional | default = 1)
        - Nome do ficheiro para guardar
    - __sphere__:
        - Raio
        - Fatias
        - Camadas
        - Nome do ficheiro para guardar
    - __cone__:
        - Raio da base
        - Altura
        - Fatias
        - Camadas
        - Nome do ficheiro para guardar

___
# Motor
- Argumentos:
    - Nome do ficheiro _.xml_ (procura dentro da pasta xml que está na pasta motor)
- Opções do menu:
    - __Fill__
        ```
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        ```

    - __Line__
        ```
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        ```

    - __Point__
        ```
        glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
        ```

- Teclado:
    - __Seta cima:__
        - roda para cima
    - __Seta baixo:__
        - roda para baixo
    - __Seta direita:__
        - roda para a direita
    - __Seta esquerda:__
        - roda para a esquerda
    - __Page up:__
        - aproxima dos objectos
    - __Page down:__
        - afasta dos objectos
