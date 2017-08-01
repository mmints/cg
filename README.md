## Computergrafik (OpenGL)

In der Computergrafik werden hauptsächlich Shader geschrieben. In CG-1 benutzen wir die Grafik-API OpenGL 3.3 . Hierzu werden spezielle Befehle im Haupt- und Shaderprogramm benötigt um auf der OpenGL-Pipeline zu agieren.

### Projekterstellung im Hauptprogramm

#### Shader linken und nutzen

Um Shaderprogramme nutzen zu können müssen sie im Hauptprogramm mit einem Datenpfad oder direkt als ein Char hinterlegt werden. Danach muss der Shader als solcher "erkannt" und zum Compiler geschickt werden. Dies übernimmt in der CG-1 _CVKShaderSet_.

```cpp
const char *shadernames[2] =
    {
        SHADERS_PATH "/04_Solution/minimal.vert", //Vertex Shader
        SHADERS_PATH "/04_Solution/minimal.frag" // Fragment Shader
    };

CVKShaderSet shaderProgram(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames); // Shaderprogramm
```

#### Buffer anlegen (Vertex Buffer Object)

#### Geometrien linken

Geometrien Werden als ein einfachen Array mit den Koordinaten in der main des Hauptprogramms angelegt oder aus Headerdateien importiert.

```cpp
GLfloat vertices[] = {/*Hier stehen die Koordinaten der Vertices*/};
```

Damit das Objekt auch dargestellt werden kann, muss in der Render Loop der draw Befehl aufgerufen werden. Es gibt verschiedene Möglichkeiten um Primitive Formen zu Rasterisieren.

```cpp
glDrawArray(GL_TYPE, 0, VERTEX_COUNT);
```

`VERTEX_COUNT` ist die Anzahl der im Array hinerlegten Vertices

`GL_TYPE` ist nur ein Platzhalter für viele verschiedene mögliche Zusammensetzfunktionen. Die Gängigsten sind:

```cpp
GL_TRIANGLES         // Zusammensetzen von je 3 Vertecies zu einen Dreieck
GL_TRIANGLE_STRIP    // Aufspannen von einem Dreieck zw. jeder Nachbarschaft
...
```

Man kann eine Geometrie nicht nur ein mal sonder auch öfter darstellen, dazu muss man lediglich den `draw`Aufruf ein weiters mal in der Render Loop aufrufen. Man muss jedoch Transformationen durchführen, um dies zu tun! Außerdem muss man vor jedem neuen "Zeichen" der Geometrie die Transformationsmatrix einer Location zuweisen, auch wenn dies schon vorher passiert ist. Was das alles genau bedeutet kommt später.

### Basis Shader

Hier sind jeweils eine simpler Vertex- und Fragment-Shader gezeigt, die auf das minimalste reduziert sind.

#### Vertex-Shader

```cpp

```

#### Fragment-Shader

```cpp

```

### Variablen/ Matrizen linken mit Uniformvariablen

Uniform Variablen werden im Shader genutzt und nicht verändert. Sie werden direkt aus dem Hauptprogramm in den jeweiligen Shader geladen. Im Hauptprogramm kann man diese Uniformvariablen verändern, z.B. in der Render Loop.

Man kann Uniformvariablen einer konkreten `location` zuweisen, oder diesen schritt sein lassen und OpenGL die Zuweisung überlassen.

```cpp
layout (location = 0) uniform vec4 position; // position wird auf 0 übergeben
```

Wenn man keine konkrete `location`angeben will/kann tut man dies auf folge weise:

```cpp
GLint glGetUniformLocation(GLuint program, const GLchar *name);
```

`glGetUniformLocation()` gibt an sich die locationnummer zurück, die OpenGL oder man selbst der Variable zugewiesen hat.

`GLuint program`ist die ID des Shader-Programms. In CG-1 kommt in der Regel an diese Position:

```cpp
shaderProgram.getProgramID()
```

Bei `const GLchar *name` geben wir als einfachen Char den Namen der Uniform-Variable im Shader an, zum Beispiel:

_Shader_

```cpp
#version 330
...
uniform int value;
...
```

_Hauptprogramm_

```cpp
GLint locValue = glGetUnifornLocation(shaderProgram.getProgramID(), "value");

...
 shaderProgram.UseProgram(); // Ausführen des Shaders (in CG-1 so)
 int value = 42;
 glUniform1i(locValue, value);
```

Im Beispiel finden man den Aufruf `glUniform1i`. In OpenGL gibt es noch eine größere Vielfalt an möglichen Uniform-Typen:

```cpp
TODO
```

Für uns ist jedoch das Linken von Matrizen am interessantesten! Um Matrizen einer `location` zu binden gibt es folgende aufrufen:

```cpp
//floating-point
glUniformMatrix2fv(...);
glUniformMatrix3fv(...);
glUniformMatrix4fv(GLint location, GLuint count,
                    GLboolean transpose, const GLfloat *m);

//double
glUniformMatrix2dv(...);
glUniformMatrix3dv(...);
glUniformMatrix4dv(GLint location, GLuint count,
                    GLboolean transpose, const GLdouble *m);
```

Da wir keine anderen Matrizen verwenden, die anders dargestellt werden als im standard OpenGL bleibt in CG-1 `GLboolean transpose` auf `GL_FALSE`.

Da wir GML als Mathebilbliothek für unsere Matrizen verwenden und der Matrizentyp nicht direkt von OpenCL als Referenz akzeptiert wird, müssen wir einen kleinen Umweg gehen und die Matrizen auf folgende Art einer `location`zuweisen.

Auf die Referenz kommt folgendes:

```cpp
glm::mat4 matrix;
glm::value_ptr(matrix);
```

### Render Loop

In der Rendershleife werden alle angelegten Vertecies durch die Pipeline geschickt und so auf dem Bildschirm dargestellt.

```cpp
while(!glfwWindowShouldClose(window))
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// Hier drin stehen die Aufrufe die immer wieder neu aktualisiert werden müssen.
    glDrawArrays(GL_[TYP], 0, [COUNT]);
}
```

### Transformationen

Im Kapitel über Uniformvariabeln haben wir bereits gelernt, wie man Matrizen an die Shader übergibt. Da wir bei Transformationen fast nur mit Matrizen arbeiten, wiederholen wir an dieser stelle nochmal, wie man Matrizen linkt.

_Shader:_

```cpp
#version 330

uniform mat4 superMatrix;
...
```

_Setzen der Location:_

```cpp
GLint locSuperMatrix =
        glUniformLocation (shaderProgram.UseProgram(), "superMatrix");
```

_Binden einer Matrix an eine Location (immer nach dem Shader-Aufruf):_

```cpp
shaderProgram.UseProgram();

glm::mat4 supermatrix = glm::mat4(1.0f); // einfach eine Einheitsmatrix
glUniformMatrix4fv(locSuperMatrix, 1, GL_FALSE, superMatrix);
```

Die folgenden Transformationsmatrizen werden nun im GLM-Syntax dargestellt:

#### Translation

```cpp
glm::translate(M, v);
`
```

`M`entspricht der vorhandenen Matrix, zu der die Translation draufmultipliziert wird. `M`ist vom Typ: `glm::mat4`

`v` ist der Vektor, um den Verschoben wird. `v`ist von Typ: `glm::vec3`

#### Skalierung

```cpp
glm::scale(M, v);
```

`M`ist das gleiche wie bei der Translation. `v`ist nun aber die Diagonale der Matrix, ist jedoch aber auch vom Typ ``glm::vec3```

#### Rotation

```cpp
glm::rotate(M, a, v);
```

`M` wie oben auch `a` ist der Winkel um den gedreht wird (in Grad); vom Typ `float` `v`die Achse um die gedreht wird; vom Typ: `` `glm::vec3``

#### Normalen

Um Normalen zu transformieren muss man die **transponierten Inversen** der Transformationsmatrix benutzen.

```cpp
glm::transpose(glm::inverse(M));
```

`M`Sei eine Matrix.

### Kamera, Viewport und Projektion

#### Kamera

Die Kamera wird durch 3 Parameter angegeben:

- `A` Die Position der Kamera in der Welt
- `C` Der "Fokuspunkt" der Kamera
- `up` Ein Vektor der angibt wo oben ist

Aus diesen 3 Parametern kann man die viewMatrix ausrechnen. Die mathematischen Details sind erstmal egal. GLM liefert uns schon eine fertige Funktion zum berechnen der Matrix:

```cpp
glm::mat4 viewMatrix = glm::lookAt(A, C, up);
```

Diese Matrix kann wie jede andere auch über eine Uniformvariable an das Shader-Programm weiter gegeben werden, voranging natürlich an den Vertex-Shader.

#### Viewport

der Viewport ist sozusagen das Tor in unsere graphische Welt. Das besondere ist, dass wir mehrere solcher Tore öffnen können und unsere Welt auf diese Weise von verschiedenen Seiten gleichzeitig betrachtet können.

Der `Default ViewPort`hat die Größe des Fensters, dass von GLEW aufgespannt wird. Man kann ihn jedoch auch manuell erstellen:

```cpp
glViewport(X, Y, WIDTH, HEIGHT);
```

- `X`ist der Ursprung auf der X-Achse
- `Y`ist der Ursprung auf der Y-Achse
- `WIDTH`ist die Breite
- `HEIGHT`ist die Höhe

**ACHTUNG:** Der Ursprung eines Viewports ist **oben rechts**!

#### Projektion

Es gibt 2 Arten eine Projektion durchzuführen.

1. Orthographisch
2. Perspektivisch

In diesem Kapitel vernachlässigen wir die mathematischen Grundvoraussetzungen.

##### Orthographische Projektion

Alle Geometrien werden Mathematisch korrekt auf der Bildebene dargestellt, d.h. unter anderem, das parallele Linien parallel bleiben und keinen Zerrfaktor bekommen. Diese Art der Projektion wird vorrangig in der 2D-Grafik verwendet.

Mit Hilfe von GLM lässt sich eine Matrix aufbauen, die die Scene in ein Kanonischen Volumen Rendert:

```cpp
glm::ortho(left, right, bottom, top, near, far);
```

_Hier wäre eine Grafik super_

##### Perspektivische Projektion

Die Matrix zur perspektivischen Projektion wird durch die Homogene Koordinate berechnet, die eine Verzerrung der Geometrien zu einen Fluchtpunkt verursacht. Die Matrix lässt sich graphisch als ein Frustom beschreiben.

--------------------------------------------------------------------------------

_Allgemein:_

```cpp
glm::frustum(left, right, bottom, top, near, far);
```

--------------------------------------------------------------------------------

_Symmetrisch (Wird für unsere Fälle am meisten verwendet!):_

```cpp
glm::perspective(angle, aspect, near, far);
```

- `angle`: Öffnungswinkel in Bogenmaß; `glm::radians(winkel°)` verwenden
- `aspect`: `width / height`; Maße des Fenstern
- `near`, `far`: Rendergrenzen

### Full Vertex-Shader

Mit diesem Einschub soll ein (fast) vollständiger Vertex-Shader gezeigt werden, in dem alle möglichen Arten von Matrizen verrechnet werden.

--------------------------------------------------------------------------------

_Hauputprogramm:_

```cpp
//...SHADER LADEN...//

// Location fuer Matrizen angeben
GLint modelMatrixHandle =
    glGetUniformLocation(shaderProgram.getProgramID(), "modelMatrix");

GLint viewMatrixHandle =
    glGetUniformLocation(shaderProgram.getProgramID(), "viewMatrix");

GLint projectMatrixHandle=
    glGetUniformLocation(shaderProgram.getProgramID(), "projectMatrix");

[...]

shaderProgram.UseProgram();

// Das folgende kann natürlich auch in der Render Loop stehen, hauptsache nach dem Shader-Program-Aufruf

// ViewMatrix
glm::mat4 viewMatrix =
glm::lookAt(glm::vec3(4.0, 4.0, -4.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
glUniformMatrix4fv(viewMatrixHandle, 1, GL_FALSE, value_ptr(viewMatrix));

// ModelMatrix
glm::mat4 modelMatrix = glm::mat4(1.0);
glUniformMatrix4fv(modelMatrixHandle, 1, GL_FALSE, value_ptr(modelMatrix));

// ProjectMatrix
glm::mat4 projectMatrix =
glm::perspective(glm::radians(60.0f), width/(float)height, 0.01f, 50.0f);
glUniformMatrix4fv(projectMatrixHandle, 1, GL_FALSE, value_ptr(projectMatrix));
```

--------------------------------------------------------------------------------

_Vertex Shader_:

```cpp
#version 330

in vec4 positionAttribute;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectMatrix;

main()
{
gl_Position= projectMatrix * viewMatrix *modelMatrix * positionAttribute;
}
```

### Beleuchtung

In diesem Bereich beschränke ich mich af das Phong-Beleuchtungsmodell, bzw. auf den Phong-Shader und daraus resultierende Abwandlungen wie den Toon-Shader.

#### Phong Beleuchtungsmodell (Mathematik)

_Die Bekannte Phong-Licht-Formel:_ $$ L = M_d \cdot L_a + \sum_{i = 1}^{#L_q} (M_d \cdot \cos\phi_i + M_s \cos^n\psi_i) \cdot L_i $$

- $$$M_d$$$: diffuse Materialfarbe
- $$$M_s$$$: speculare Materialfarbe
- $$$L_a$$$: ambiente Lichtfarbe
- $$$L_i$$$: Lichtfarbe (Quelle)
- $$$n$$$: Glanzzahl
- $$$\phi_i$$$: Winkel zw. Normale und Lq
- $$$\psi_i$$$: Winkel zw. Blickrtg. und Reflektion

#### Bereitstellen der Normalen zur Interpolation im Vertex-Shader

Die Normalen müssen zu aller erst an den Shader über eine Uniform-Variable, bzw. direkt über eine Location übergeben werden.

```cpp
// Vertex-Shader
layout (location = 1) in vec3 normalAttribute; // oder vec4
```

Die Normalen müssen in das passnede Koordinatensystem transformiert werden. Die Dafür benötigten Matrizen sind in der Regel bereits vorhanden. Normalen werden durch die transponierte Inverse eine Matrize transformiert.

```cpp
[...]

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
[...]
out vec3 passNormal; // oder vec4; übergabe an den Fragment-Shader
                    //Interpoliert nacht übertagung!

void main()
{
    gl_Position = ... // Das was hier immer steht
    vec4 n = transpose(
        inverse(
            viewMatrix * modelMatrix
               )
       ) * normalAttribute; //ggf. drauf achten dass es vec3 ist!

    passNormal = normalize(n.xyz);    // Auf die länge 1 normieren
                                      // auch hier wegen vec3 /vec4!
}
```

Im Frangment-Shader werden außerdem die Positionen der Vertecies benötigt. Diese Müssen auch in das richtige Koordinatensystem transformiert werden. Um in das Kamerakoordinatensystem zu gelagen muss jediglich dich Projektionsmatrix ausgelassen werden

```cpp
[...]
out vec4 passPosition; //hier auch vec4 oder vec3
void main()
{
    passPosition = viewMatrix * modelMatrix * positionAttribute;
}
```

Auch hier schreibe ich extra noch einmal! Man muss darauf achten, als was die jeweiligen Vektoren übergeben! entweder mit oder ohne Homogene Koordinate! Falls ohne muss bei den Normalen `0` am `vec4`dazugepackt werden. Analog bei den Vertex-Positionen `1`.

--------------------------------------------------------------------------------

Fall auf keine andere Art und Weise die Lichtquellenposition übergeben wird, muss diese Analog zu Vertex-Position an den Fragment-Shader übergeben werden.

```cpp
[...]
uniform vec3 lightPosition;

out vec3 lightPosition; //hier auch vec4 oder vec3
void main()
{
    lightPosition = (viewMatrix * vec4(lightPosition,1))xyz;
}
```

#### Berechnen der Vektoren im Frangmentshader

```cpp
//compute the light vector as the normalized vector between
//the vertex position and the light position:
vec3 lightVector = normalize(lightPosition - passPosition.xyz);

//compute the eye vector as the normalized negative vertex position in camera coordinates:
vec3 eye = normalize(-passPosition.xyz);

//compute the normalized reflection vector using GLSL's built-in reflect() function:
vec3 reflection =
    normalize(reflect(-lightVector, normalize(passNormal)));
```

#### Berechnung des Lichts

Aus der resultierenden Phong-Formel lässt die Berechnung des diffusen und des specularen Lichtteils eines Materials ausrechnen. Zunächst brachen wir dafür die Material- und Lichtfarben. Diese werden entweder aus dem Hauptprogramm als uniform an den Fragment-Shader übergeben oder dort direkt gesetzt.

Diese Farben werden anschließend über eine Formel zur Beleuchtung verrechnet, z.B. durch Phong oder Toon.

--------------------------------------------------------------------------------

_Berechnung der diffusen Intensität:_

```cpp
cos_phi = max(dot(lightVector, normal), 0);
```

--------------------------------------------------------------------------------

_Berechnung der specularen Intensität:_

```cpp
cos_psi = pow(max(dot(reflection, eye), 0),n);
```

--------------------------------------------------------------------------------

Anschließend kann man die Beleuchtung beliebig zusammensetzen.

### Texturen

_lasse ich aus_

### Transparenz

_lasse ich aus_