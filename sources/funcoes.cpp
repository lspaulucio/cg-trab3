#include "funcoes.h"

extern Janela MainWindow;
extern Circulo player;
extern Circulo arena[2];
extern Retangulo rect;
extern vector<Circulo> enemies;
extern int key_status[256];

void readXMLFile(const char *path)
{
    const char config_file_name[] = "config.xml";

    string svg_name, svg_type, svg_path, pathFile;
    XMLDocument config_file, svg_file;
    XMLError statusLoad;
    XMLElement *pElem;
    XMLNode *pRoot;

    if(!path) //Verify if the path was provided
    {
        cout << "Path to config file not provided, the program will be finished" << endl;
        exit(1);
    }

    pathFile = path;
    pathFile += config_file_name;
    //cout << pathFile << endl;

    //Opening file
    statusLoad = config_file.LoadFile(pathFile.c_str());

    if(statusLoad != XML_SUCCESS) //Test if file has been opened correctly
    {
        cerr << "Error opening configuration file\nProgram will be finished" << endl;
        exit(XML_ERROR_FILE_READ_ERROR);
    }

    pRoot = config_file.FirstChild(); //Get first element

    if(!pRoot)
    {
        cerr << "Error parsing element on configuration file\nProgram will be finished" << endl;
        exit(XML_ERROR_PARSING_ELEMENT);
    }
    //cout << pRoot->Value() << endl;

    //config.xml file
    pElem = pRoot->FirstChildElement("arquivoDaArena");
    svg_name = pElem->FindAttribute("nome")->Value();
    svg_type = pElem->FindAttribute("tipo")->Value();
    svg_path = pElem->FindAttribute("caminho")->Value();

//    cout << name << endl;
//    cout << type << endl;
//    cout << svg_path << endl;

    //Path and name to svg file

    if(svg_path[0] == '~') //Testing if there is a tilde on beginning of path
    {
        pathFile = getenv("HOME");
        svg_path.erase(0,1);
        pathFile += svg_path;
        // cout << pathFile << endl;
    }
    else
    {
        pathFile = svg_path;
    }

    pathFile += svg_name += ".";
    pathFile += svg_type;

    // cout << pathFile << endl;

    //SVG file
    statusLoad = svg_file.LoadFile(pathFile.c_str());

    if(statusLoad != XML_SUCCESS) //Test if file has been opened correctly
    {
        cerr << "Error opening svg file\nProgram will be finished" << endl;
        exit(XML_ERROR_FILE_READ_ERROR);
    }

    pRoot = svg_file.FirstChild(); //Get first element

    if(!pRoot)
    {
        cerr << "Error parsing element on svg file\nProgram will be finished" << endl;
        exit(XML_ERROR_PARSING_ELEMENT);
    }
//    cout << pRoot->Value() << endl;

    pElem = pRoot->FirstChildElement();
    // cout << pElem->Value() << endl;

    for(; pElem != NULL; pElem = pElem->NextSiblingElement())
    {
        string tipo = pElem->Value();

        if(!tipo.compare("circle")) //If is a circle
        {
            Circulo c;
            c.setXc(atof(pElem->FindAttribute("cx")->Value()));
            c.setYc(atof(pElem->FindAttribute("cy")->Value()));
            c.setRadius(atof(pElem->FindAttribute("r")->Value()));
            c.setId(pElem->FindAttribute("id")->Value());
            c.setRGBColors(pElem->FindAttribute("fill")->Value());

            // cout << pElem->FindAttribute("cx")->Value() << endl;
            // cout << pElem->FindAttribute("cy")->Value() << endl;
            // cout << pElem->FindAttribute("r")->Value() << endl;
            // cout << pElem->FindAttribute("id")->Value() << endl;
            // cout << pElem->FindAttribute("fill")->Value() << endl;

            //cout << "Circulo " << "cx: " << c.getXc() << " cy: " << c.getYc() << " r: " << c.getRadius() <<
            //" colors: " << c.getRGBColors(RED) << ", " << c.getRGBColors(GREEN) << ", " << c.getRGBColors(BLUE) << endl;
            if(!c.getId().compare("Jogador"))
                player = c;
            else if(!c.getId().compare("Pista"))
                {
                    if(arena[0].getRadius() > c.getRadius())
                        arena[1] = c;
                    else{
                            arena[1] = arena[0];
                            arena[0] = c;
                        }
                }
                else enemies.push_back(c);
        }
        else if(!tipo.compare("rect")) //If is a rectangle
            {
                rect.setXc(atof(pElem->FindAttribute("x")->Value()));
                rect.setYc(atof(pElem->FindAttribute("y")->Value()));
                rect.setWidth(atof(pElem->FindAttribute("width")->Value()));
                rect.setHeight(atof(pElem->FindAttribute("height")->Value()));
                rect.setId(pElem->FindAttribute("id")->Value());
                rect.setRGBColors(pElem->FindAttribute("fill")->Value());

                // cout << pElem->FindAttribute("cx")->Value() << endl;
                // cout << pElem->FindAttribute("cy")->Value() << endl;
                // cout << pElem->FindAttribute("r")->Value() << endl;
                // cout << pElem->FindAttribute("id")->Value() << endl;
                // cout << pElem->FindAttribute("fill")->Value() << endl;

                // cout << "Retangulo " << "x: " << rect.getXc() << " y: " << rect.getYc() <<
                // " width: " << rect.getWidth() << " height: " << rect.getHeight() << " colors: " <<
                // rect.getRGBColors(RED) << ", " << rect.getRGBColors(GREEN) << ", " << rect.getRGBColors(BLUE) << endl;
            }
    }//End of file read

    MainWindow.setHeight(2*arena[0].getRadius());
    MainWindow.setWidth(2*arena[0].getRadius());
    MainWindow.setTitle("Arena");

    //Adjusting Y-Axis -> y = hy - y;
    for(int i = 0; i < 2; i++)
        arena[i].setYc(MainWindow.getHeight() - arena[i].getYc());

    rect.setYc(MainWindow.getHeight() - rect.getYc());
    rect.updateVertices();
    // cout << "x: " << rect.getXc() << "y: " << rect.getYc() << endl;

    for(vector<Circulo>::iterator it = enemies.begin(); it != enemies.end(); it++)
        (*it).setYc(MainWindow.getHeight() - (*it).getYc());

    player.setYc(MainWindow.getHeight() - player.getYc());

    // for(vector<Circulo>::iterator it = enemies.begin(); it != enemies.end(); it++)
    //     cout << (*it).getId() << endl;

    return;
}

//OpenGL functions

void drawRectangle(float x1, float y1, float x2, float y2, const float colors[3])
{
    glColor3fv((GLfloat*)(colors));
    glBegin(GL_POLYGON);
        glVertex3f(x1, y1, 0.0);
        glVertex3f(x1, y2, 0.0);
        glVertex3f(x2, y2, 0.0);
        glVertex3f(x2, y1, 0.0);
    glEnd();
}

void drawCircle(float xc, float yc, float radius, const float colors[3], int resolution)
{
    float dx, dy;
    glColor3fv((GLfloat*)(colors));
    glBegin(GL_TRIANGLE_FAN);
		glVertex2f(xc, yc);
		for(int i = 0; i <= resolution; i++)
        {
            dx = xc + (radius * cos(i * 2.0*M_PI / resolution));
            dy = yc + (radius * sin(i * 2.0*M_PI / resolution));
			glVertex2f(dx, dy);
		}
    glEnd();
}

void init(void)
{
    GLfloat xi, xf;
    GLfloat yi, yf;

    /*Selecting background color*/
    //cout << " Janela "<< MainWindow.getBgColors(RED) << MainWindow.getBgColors(GREEN) << MainWindow.getBgColors(BLUE) << endl;
    glClearColor(MainWindow.getBgColors(RED),MainWindow.getBgColors(GREEN),MainWindow.getBgColors(BLUE), 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    xi = arena[0].getXc() - arena[0].getRadius();
    xf = arena[0].getXc() + arena[0].getRadius();
    yi = arena[0].getYc() - arena[0].getRadius();
    yf = arena[0].getYc() + arena[0].getRadius();

    glOrtho(xi,xf,yi,yf,-1.0,1.0);
}

void display(void)
{
    /*Cleaning pixels */
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i=0; i < 2; i++)
        arena[i].draw();

    rect.draw();

    for(vector<Circulo>::iterator it = enemies.begin(); it != enemies.end(); it++)
        (*it).draw();

    player.draw();

    glutSwapBuffers();
}

void idle(void)
{
    float dx = 0, dy = 0;
    float tx, ty;
    const float STEP = 1;

    if(key_status['w'])
        dy += STEP;
    if(key_status['s'])
        dy -= STEP;
    if(key_status['d'])
        dx += STEP;
    if(key_status['a'])
        dx -= STEP;

    tx = player.getXc();
    ty = player.getYc();

    bool teste = true;

    // Test new position x
    player.setXc(tx + dx);

    for(vector<Circulo>::iterator it = enemies.begin(); it != enemies.end(); it++)
    {
        teste = teste && (*it).outsideCircle(player);
    }

    if(arena[0].insideCircle(player) && arena[1].outsideCircle(player) && teste);
    else
    {
        player.setXc(tx);
    }

    // Test new position y
    player.setYc(ty + dy);

    for(vector<Circulo>::iterator it = enemies.begin(); it != enemies.end(); it++)
    {
        teste = teste && (*it).outsideCircle(player);
    }

    if(arena[0].insideCircle(player) && arena[1].outsideCircle(player) && teste);
    else
    {
        player.setYc(ty);
    }

    glutPostRedisplay();
}

void keyUp (unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
        case 'W':
          key_status['w'] = 0;
          break;

        case 's':
        case 'S':
          key_status['s'] = 0;
          break;

        case 'd':
        case 'D':
          key_status['d'] = 0;
          break;

        case 'a':
        case 'A':
          key_status['a'] = 0;
          break;
      }
}

void keypress (unsigned char key, int x, int y)
{
  switch (key)
  {
      case 'w':
      case 'W':
        key_status['w'] = 1;
        break;

      case 's':
      case 'S':
        key_status['s'] = 1;
        break;

      case 'd':
      case 'D':
        key_status['d'] = 1;
        break;

      case 'a':
      case 'A':
        key_status['a'] = 1;
        break;

    //   case 'e':
    //     exit(1);
  }
}
