# CV Programmier Training

[TOC]

Mit diesen Projekt möchte ich für meine kommende Cv-Programmierklausur üben. Es werden beide großen Themen Computergrafik und Bildverarbeitung behandelt. In diesem README werden alle wichtigen Code-Stücke Dokumentiert und detailliert kommentiert.

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

## Bildverarbeitung

### Statistik ausrechnen

#### Mittelwert
Man rechnet die Summe aller Werte der Pixel aus und Teilt diese anschließend durch die gesamte Pixelzahl.

$$\mu := \frac{1}{|Loc|} \cdot \sum_{p \epsilon Loc} I(p)$$

#### Standardabweichung
Die Standardabweichung gibt an, wie weit auseinander die Werte der Pixel sind.

#### Varianz
Die Varianz ist das Quadrat der Standardabweichung und berechnet sich folgender maßen:

$$\sigma^2 := \frac{1}{|Loc|} \cdot \sum_{p \epsilon Loc} (I(p) - \mu)^2 $$

---
Beim Programmieren muss man umbedingt darauf achten, dass man einen Wertebereich wählt, der groß genug ist, z.B. ``double``.
```cpp
int N = img.width() * img.height;
double sum = 0.0;
double sumq = 0.0;

for (int i = 0; ...){
	for (int j = 0; ...){
    	int val = img[i][j];
        sum += val;
        sumq += val * val;
    }
}

double mu = N / sum;
double var = sumq / N - mu * mu;
double std_dev = sqrt(var);
```

#### Sum of Squared Differences (SSD)
```cpp
float ssd(const SimpleGrayImage &in1, const SimpleGrayImage &in2)
{
	if (in1.height() != in2.height() || in1.width() != in2.width())
 		throw "ssd: Bilder müssen gleiche Größe haben";

	float sum = 0.0;
	
    for (int i = 0; i < in1.height(); i++) {
		for (int j = 0; j < in1.width(); j++) {
			float dif = in1[i][j] - in2[i][j];
			sum += dif * dif;
		}
	}
return sum;
```

### Histogramme

```cpp
void historam (const SimpleGrayImage &img, long (&tab)[256])
{
	for ( int k = 0; k < 256; k++){
    	tab[k] = 0; // Tabellen clearen
    }
    
    for (int i = 0;...){
    	for (int j = 0;...){
        	tab[img[i][j]] ++;
        }
    }
}
```

#### Histogrammspreizung

```cpp
void hist_spread_lut(const long (&hist)[256], int (&lut)[256])
{
	int min = 0;
    int max = 255;
    
    while (hist[min] <= 0 && min < 255){
    	min++; //Rutsche von unten an minimum ran
	}
    while (hist[max] <= 0 && max > 0){
    	max--; //Rutsche von oben an max ran
    }
    
    if (min > max) throw std::runtime_error;
    
	for (int i = 0; i < 256; i++){
	      lut[i] = 255 * (i - min)/(max - min);
	}
}
```


### Look Up Tabellen (LUT)
In Look-Up-Tabellen werden werte gespeichert um ein Program effektiver zu machen. So muss man z.b. nich bei Iterieren über ein Bild für jedes Pixel auf neue eine Funktion berechnen sonder kann einfach in der Tabelle "nachschauen".

Das hat vor allem bei Histogrammen einen großen Mehrwert!

```cpp
void apply_lut(const SimpleGrayImage &in, SimpleGrayImage &out, int (&lut) [256])
{
	out.resize(in.width(), in.height());
	out.clear();

	for (int i = 0; i < in.height(); i++)
	{
		for (int j = 0; j < in.width(); j++)
		{
			out[i][j] = lut[in[i][j]];
		}
	}
}

```


### Filter Generieren

#### Mittelwertfilter

So lässt sich ein Mittelwertfilter generieren:

```cpp
void genMeanKernel (int n, SimpleFloatImage &kern)
{
	if (n % 2 != 1) throw std::runtime_error ("n muss ungerade sein");
    kern.resize(n, n);
    kern.clear(1.0/(n*n));
}
```
So ergibt sich beispielsweise ein 3 x 3 Mittelwertfilter mit 9 Einträgen je mit dem Wert 1/9.


#### Binomialfilter

Zur Berechnung eines Binomialfilters muss man die Binomialkoeffizienten ausrechnen. Im Codebeispiel passiert dies durch eine Hilfsfunktion, die die Ungeraden Zeilen des pacalischen Dreiecks zurück gibt

```cpp
void binom_mask(SimpleFloatImage &bmask, int mrad)
{
  int mwid = 2*mrad + 1;
  int pascal[100];
  if (mrad < 1 || mwid > 33) // integer overflow in pascal_zeile ab mwid=35
    throw "binom_mask: mrad zu groß oder < 1";
  bmask.resize(mwid, mwid); // bmask MUSS diese Größe bekommen
  pascal_zeile(pascal, mwid);
  double sum = pow(2.0, 2*(mwid-1)); // kann man so ausrechnen ...
  for (int i = 0; i < mwid; i++)
    for (int j = 0; j < mwid; j++) {
      double val = pascal[i] * double(pascal[j]);
      bmask[i][j] = val / sum;   // Normalisieren, damit die Gesamt-Summe 1 ist
    }
}
```

### Randbehandlung

### Separable Filter anwenden

In diesem Code ist eine Randbehandlung bereits integriert:
```cpp
void sepFilter2(const SimpleGrayImage &in,
				SimpleFloatImage &out,
				const std::vector<float> &maskH,
				const std::vector<float> &maskV)
{
	if ((maskH.size() % 2) == 0)
    	throw std::runtime_error("kantenläne muss ungerade sein");
	if (maskH.size() != maskV.size())
    	throw std::runtime_error("Maske muss quadratisch sein");

	out.resize(in.width(), in.height());
	out.clear(255);

	SimpleFloatImage temp(in.width(), in.height());
	temp.clear(255);

	// Radius der Maske setzen
	int r = (maskH.size() - 1) / 2;

	// Ergebnis, dass nach anwendung der Maske auf den jeweiligen pixel geschrieben wird
	double pixelValue = 0;

	//hilfsvariablen zum positionieren der Maske auf dem Bild
	int n = 0;
	int m = 0;

	//hilfsvariablen zur behandlung des randes
	int my = 0;
	int nx = 0;

	//Horizontalen Kern anwenden
	for (int i = 0; i < in.height(); i++)
	{
			for (int j = 0; j < in.width(); j++)
			{
				pixelValue = 0;
				n = i - r;
				for (int x = 0; x < maskH.size(); x++)
				{
					nx = n + x;

					if(nx < 0)
					{
						nx = -nx;
					}
					else if (nx >= in.height())
					{
						nx = (2 * in.height()) -nx -r;
					}
					m = j - r;
					pixelValue += in[nx][j] * maskH[x];
				}
				temp[i][j] = pixelValue;

			}
	}
	//Vertikalen Kern anwenden
	for (int i = 0; i < in.height(); i++)
	{
			for (int j = 0; j < in.width(); j++)
			{
				pixelValue = 0;
				m = j - r;
				for (int y = 0; y < maskV.size(); y++)
				{
					my = m + y;

					if (my < 0)
					{
						my = -my;
					}

					else if (my >= in.width())
					{
						my = (2 * in.width()) -my -r;
					}
					pixelValue += temp[i][my] * maskV[y];
				}

				out[i][j] = pixelValue;
			}
	}

}

```

### Sobel

Es gibt 2 Sobeloperatioren, einen zur Vertikalen Kantendedektion und einen zur Horizontalen.
Diese sehen folgendermaßen aus:

$$

S_v = 
\begin{pmatrix}
-1 & 0 & 1 \\
-2 & 0 & 2 \\
-1 & 0 & 1
 \end{pmatrix}
 , 
S_h = 
\begin{pmatrix}
-1 & -2 & -1 \\
0 & 0 & 0 \\
1 & 2 & 1
 \end{pmatrix}
$$

Diese lassen sich auf diese 1D-Vekotoren zurückführen und somit separieren:
$$
x = (-1, 0, 1)
$$
$$
y = (1, 2, 1)
$$
---
Nachdem man für beide Richtungen die Sobeloperatoren auf einem Bild durchgeführt hat, kann man die beiden daraus resultierenden Bilder miteinander verrechnen.

Um die ergebnissbilder darzustellen müssen diese mit ``copyToGray()`` zu Grauwertbildern umgewandelt werden!

#### Gradientenstärke

Man muss jedeglich die beiden Ergebnissbilder miteinander "addieren".
```cpp
void city_strength(const SimpleFloatImage &sobx, const SimpleFloatImage &soby, SimpleFloatImage &str)
{
	str.resize(soby.width(), soby.height());
	for (int i = 0; i < str.height(); i++)
	{
		for (int j = 0; j < str.width(); j++)
		{
            // Formel aus dem Priesebuch
            str[i][j] = abs(sobx[i][j]) + abs(soby[i][j]);
        }
	}
}
```

#### Gradientenrichtung
```cpp
void grad_dir(const	SimpleFloatImage &sobx,
					const SimpleFloatImage &soby,
                	SimpleGrayImage &dir)
{
    dir.resize(sobx.width(), sobx.height());
    
    for (int i = 0; i < soby.height(); i++)
    {
        for (int j = 0; j < soby.width(); j++)
        {
            // Formel aus dem Priesebuch
            dir[i][j] = clampToByte((atan2(soby[i][j], sobx[i][j])*90)/M_PI+90);
        }
    }  
}

```

### Morphologie
In der Morphologie wird mit Strukturelementen gearbeitet. Diese sind eine Art Markerfilter mit denen die über das Bild gegangen wird und die Erosion, bzw. Dilatation berechnet wird.

In der Regel wird schwarz (0) als Hintergrund und Weiß (255) als Vordergrund in einem Bild gesehen.

#### Dilatation
Die Dilatation vergrößert Bildobjekte, d.h. sie macht die weißen Bereiche Größer.

```cpp
void dilatation (const SimpleGrayImage &inImg, const SimpleGrayImage &inSE, SimpleGrayImage &outImg)
{
    outImg.resize(inImg.width(), inImg.height());
    outImg.clear();
    
    //hilfsvariablen zum positionieren der Maske auf dem Bild
    int n = 0;
    int m = 0;
    
    //hilfsvariablen zur behandlung des randes
    int my = 0;
    int nx = 0;
    
    // Ergebnis, dass nach anwendung der Maske auf den jeweiligen pixel geschrieben wird
    int pixelValue;
    
    // Radius der Maske setzen
    int r = (inSE.width() - 1) / 2;
    
    
    for (int i = 0; i < inImg.height(); i++)
    {
        for (int j = 0; j < inImg.width(); j++)
        {
            pixelValue = 0;
            //"positionieren" der Maske und iterieren über die maske
            n = i - r;
            for (int x = 0; x < inSE.width(); x++)
            {
                nx = n + x;
                
                // Behandlung der randfaelle
                if(nx < 0)
                {
                    nx = 0;
                }
                else if (nx >= inImg.height())
                {
                    nx = 0;
                }
                m = j - r;
                
                for (int y = 0; y < inSE.height(); y++)
                {
                    my = m + y;
                    
                    if (my < 0)
                    {
                        my = 0;
                    }
                    
                    else if (my >= inImg.width())
                    {
                        my = 0;
                    }
                    if (inImg[nx][my] == 255 && inSE[x][y] == 1)
                    {
                        pixelValue = 255;
                        break;
                    }
                }
            }
            outImg[i][j] = pixelValue;
        }
    }

}


```

#### Erosion
Die Erosion verkleinert die weißen Bereiche.

```cpp
void erosion (const SimpleGrayImage &inImg, const SimpleGrayImage &inSE, SimpleGrayImage &outImg)
{
    outImg.resize(inImg.width(), inImg.height());
    outImg.clear();
    
    //hilfsvariablen zum positionieren der Maske auf dem Bild
    int n = 0;
    int m = 0;
    
    //hilfsvariablen zur behandlung des randes
    int my = 0;
    int nx = 0;
    
    // Ergebnis, dass nach anwendung der Maske auf den jeweiligen pixel geschrieben wird
    int pixelValue;
    
    // Radius der Maske setzen
    int r = (inSE.width() - 1) / 2;
    
    
    for (int i = 0; i < inImg.height(); i++)
    {
        for (int j = 0; j < inImg.width(); j++)
        {
            pixelValue = 255;
            //"positionieren" der Maske und iterieren über die maske
            n = i - r;
            for (int x = 0; x < inSE.width(); x++)
            {
                nx = n + x;
                
                // Behandlung der randfaelle
                if(nx < 0)
                {
                    nx = 0;
                }
                else if (nx >= inImg.height())
                {
                    nx = 0;
                }
                m = j - r;
                
                for (int y = 0; y < inSE.height(); y++)
                {
                    my = m + y;
                    
                    if (my < 0)
                    {
                        my = 0;
                    }
                    
                    else if (my >= inImg.width())
                    {
                        my = 0;
                    }
                    if (inImg[nx][my] == 0 && inSE[x][y] == 1)
                    {
                        pixelValue = 0;
                        break;
                    }
                }
            }
            outImg[i][j] = pixelValue;
        }
    }
}

```

#### Öffnen und Schließen
Zu öffnen und schließen muss man das Struckturelement um den Mittelpunkt spiegeln:
```cpp
SimpleGrayImage pointReflection(const SimpleGrayImage &matrix)
{
    if ((matrix.width() % 2) == 0) throw std::runtime_error("kantenläne muss ungerade sein");
    if (matrix.width() != matrix.height()) throw std::runtime_error("Maske muss quadratisch seinS");
    
    // hilfsvariable um nullpunkt in die mitte der Matrix zetzen setzte
    int zero = (matrix.height() - 1) / 2;
    
    // gespielgelte matrix
    SimpleGrayImage result;
    result.resize(matrix.width(), matrix.height());
    int i_r;
    int j_r;
    
    // spiegeln
    for (int i = 0; i < matrix.height(); i++)
    {
        for (int j = 0; j < matrix.width(); j++)
        {
            i_r = i - zero;
            j_r = j - zero;
            i_r *= -1;
            j_r *= -1;
            i_r += zero;
            j_r += zero;
            
            result[i_r][j_r] = matrix[i][j];
        }
    }
    return result;
}

```

##### Öffnen
Öffnen entfernt kleine Störungen zwischen zwei Objekten des Vordergrundes.
B: Bild
S: Strukturelement
$$ 
öffnen = dilatation(erosion(B,S), S^\uparrow)
$$
```cpp
void opening (const SimpleGrayImage &inImg, const SimpleGrayImage &inSE, SimpleGrayImage &outImg)
{
    SimpleGrayImage tempImg;
    
    erosion(inImg, inSE, tempImg);
    dilatation(tempImg, pointReflection(inSE), outImg);
}
```

##### Schließen
Schließen schließt Lücken in Objekten und verschmilzt benachbarte Vordergrundobjekte.
B: Bild
S: Strukturelement
$$ 
öffnen = erosion(dilatation(B,S), S^\uparrow)
$$
```cpp
void closeing (const SimpleGrayImage &inImg, const SimpleGrayImage &inSE, SimpleGrayImage &outImg)
{
    SimpleGrayImage tempImg;
    
    dilatation(inImg, inSE, tempImg);
    erosion(tempImg, pointReflection(inSE), outImg);
}
```

#### Morphologischer Gradient

Viel kann man nicht sagen:

B: Bild
S: Strukturelement
$$ 
gradient = dilatation(B, S) - erosion(B,S)
$$
```cpp
void morphGradient (const SimpleGrayImage &inImg, const SimpleGrayImage&inSE, SimpleGrayImage &outImg)
{
    outImg.resize(inImg.width(), inImg.height());
    
    SimpleGrayImage tempImg1;
    
    SimpleGrayImage tempImg2;
    
    erosion (inImg, inSE, tempImg1);
    dilatation (inImg, inSE, tempImg2);
    
    for (int i = 0; i < outImg.height(); i++)
    {
        for (int j = 0; j < outImg.width(); j++)
        {
            outImg[i][j] = tempImg2[i][j] - tempImg1[i][j];
        }
    }
}
```
