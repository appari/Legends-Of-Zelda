#include "main.h"
#include "timer.h"
#include "boat.h"
#include "ball.h"
#include "sea.h"
#include "rock.h"
#include "gift.h"
#include "cannon.h"
#include "score.h"
#include "wind.h"
#include "booster.h"
#include "monster.h"
#include "land.h"


using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Boat boat;
Sea sea;
Wind windD;
Booster booster[1000];
Land land;

Monster monster[1000];
vector<Ball> fireBall;
vector<Ball> Aim;
Rock rock[1000];
Gift gift[1000];
bool windPresent = false;
Monster Boss;
float windDirec,windSpeed;
float mnstTimer =0;
Gift points[1000];
float ballTimer = 0;
Ball Health;
Score score;
Cannon cannon;
float eyex=5,eyey=5,eyez=0;
float tarx=0,tary=5,tarz=0;
double mouse_xpos,mouse_ypos;
int mnstActCnt=0;
int NumRock=100,NumGift=20,NumBonPoints = 25,fireBallCnt=0,NumBooster=20,NumMonster=20,Area=300,aimCount=0,noMonsterKills=0;
float boosterValue=0,mnstTime = 20;
bool boatMotion = true;
bool ort = false;
bool aimDiplay = false;
bool ticking = true;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int cam = 0;
bool First = true;
float gameTime = 10*60;
Timer t60(1.0 / 60);
Timer wave(2.0);
Timer wind(3.0);
Timer bstr(60);
Timer monstTimer(4.0);
Timer respwan_timer(1.0);
Timer boatSound(12.0);
Timer boatTimer(12.0);
Timer oceanTimer(61);
Timer bossTimer(10);
Timer seaDraw(3);
Timer game(10 * 60);
vector<Ball> drops;
vector<Ball> parts;
int noDrops = 0,noParts=0;
bool RESPWANING = false;
int last_drawn = 0;
int right_mouse_click,left_mouse_click;
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    //glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye ( eyex,eyey,eyez );
    cout << camera_rotation_angle<<endl;
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (tarx, tary, tarz);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0 );

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    Health.draw(VP);
    sea.draw(VP);
    land.draw(VP);
    for (int i = 0; i < noDrops;i++)
    {
        if(!boat.jumping)
            drops[i].draw(VP);
    }
    for (int i = 0; i < noParts;i++)
    {
        parts[i].draw(VP);
    }
    for (int i = 0; i < Aim.size();i++)
    {
        if(Aim[i].fire)
            Aim[i].draw(VP);
    }
    if (RESPWANING == true)
    {
        if (last_drawn == 0)
        {
            boat.draw(VP);
            cannon.draw(VP);
        }
        last_drawn = (last_drawn + 1) % 4;

        if (respwan_timer.processTick())
            RESPWANING = false;
        }
        else{
        boat.draw(VP);
        cannon.draw(VP);
    }
    windD.draw(VP);
    
    mnstActCnt =0;
    for (int i=0;i<NumMonster ;i++)
    {
        if(monster[i].active)
        {
           monster[i].draw(VP);
           mnstActCnt++;
        }
    }
    if(noMonsterKills<=1 && Boss.active)
    {
        Boss.active = false;
    }

    else
    {
        noMonsterKills =0;
        Boss.active = true;
    }
    if (Boss.active)
        Boss.draw(VP);
    
    for (int i=0;i<NumBooster;i++)
    {
        if(booster[i].active)
        booster[i].draw(VP);
    }
    for (int i=0;i<NumRock;i++)
        rock[i].draw(VP);
    for (int i=0;i<NumGift;i++)
        gift[i].draw(VP);
    for (int i=0;i<NumBonPoints;i++)
        points[i].draw(VP);
    for (int i=0;i<fireBallCnt;i++)
    {
        if(fireBall[i].fire)
            fireBall[i].draw(VP);
    }

}
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS) {
            left_mouse_click = 1;
            right_mouse_click =0;
        }
         if (action == GLFW_RELEASE) {
            left_mouse_click =0;
            
        }
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        if(action == GLFW_PRESS)
        {
            right_mouse_click = 1;
            left_mouse_click =0;
        }
        if (action == GLFW_RELEASE) {
        right_mouse_click = 0;
        }
        break;
    
    }
}

void tick_input(GLFWwindow *window) {
    
    if(oceanTimer.processTick()||First)
    {
        system(" canberra-gtk-play -f x  ../resources/ocean.wav ");
        First = false;
    }
    ballTimer += 0.01;
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int u = glfwGetKey(window, GLFW_KEY_U);
    
    int h = glfwGetKey(window, GLFW_KEY_H);
    int g = glfwGetKey(window, GLFW_KEY_G);
    int b = glfwGetKey(window, GLFW_KEY_B);
    int c = glfwGetKey(window, GLFW_KEY_C);
    int fire = glfwGetKey(window, GLFW_KEY_F);
    int jump = glfwGetKey(window, GLFW_KEY_SPACE);
    int bt = glfwGetKey(window, GLFW_KEY_1);
    int top_down = glfwGetKey(window, GLFW_KEY_2);
    int tower = glfwGetKey(window, GLFW_KEY_3);
    int heli = glfwGetKey(window, GLFW_KEY_4);
    int follow = glfwGetKey(window, GLFW_KEY_5);
    double mouse_pos_x,mouse_pos_y;
    glfwGetCursorPos(window,&mouse_pos_x,&mouse_pos_y);
    
    if(c)
    {
        cam = cam%5;
        cam+=1;
    }
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    if(fire)
    {
        if(ballTimer>0.5)
        {
            ballTimer =0;
            system(" afplay  ../resources/cannon.wav ");
            float speedx = 2*cos(cannon.rotation1*M_PI/180.0f)*(cos(cannon.rotation * M_PI/180.0f));
            float speedz = 2*cos(cannon.rotation1*M_PI/180.0f)*(sin(cannon.rotation * M_PI/180.0f));
            float speedy = 2*(-sin(cannon.rotation1*M_PI/180.0f));
            fireBall.push_back(Ball(cannon.position.x,cannon.position.y,cannon.position.z,speedx,speedy,speedz,0.3));
            //cout << fireBall[fireBallCnt].size<<"\n";
            fireBall[fireBallCnt].fire = true;
            fireBallCnt++;
        }
    }
    if(b)
    {
        if(boosterValue >0)
        {
            boosterValue -= 0.1;
            boat.position.x -=boat.speed*(cos(boat.rotation * M_PI/180.0f))*2;
            boat.position.z +=boat.speed*(sin(boat.rotation * M_PI/180.0f))*2;
        }
    }
    
    if(bt)
        cam = 1;
    if(top_down)
        cam = 2;
    if(tower)
        cam = 3;
    if(heli)
        cam = 4;
    if(follow)
        cam = 5;
    if(jump)
    {
        if(!boat.jumping)
        {
        
            boat.speedy = 2.5;
            boat.jumping=true;
            system(" afplay  ../resources/jump.wav ");
        }

    }
    
    
    
    if(w)
    {
        if(cannon.rotation1>-60)
            cannon.rotation1-=0.4;

    }
    if(s)
    {
        if(cannon.rotation1<0)
        cannon.rotation1+=0.4;
    }
    if(d)
    {
        cannon.rotation -= 0.5;

    }
    if(a)
    {
        
        
        float speedx = 2 * cos(cannon.rotation1 * M_PI / 180.0f) * (cos(cannon.rotation * M_PI / 180.0f));
        float speedz = 2 * cos(cannon.rotation1 * M_PI / 180.0f) * (sin(cannon.rotation * M_PI / 180.0f));
        float speedy = 2 * (-sin(cannon.rotation1 * M_PI / 180.0f));
        float posx=cannon.position.x, posy=cannon.position.y, posz=cannon.position.z;
        for (int i = 0; i < Aim.size();i++)
        {
            posx -= speedx ;
            posz += speedz;
            posy += speedy;
            speedy -= 0.02;
            Aim[i].set_position(posx, posy, posz);
            Aim[i].fire = true;
        }
    }
    else
    {
        for (int i = 0; i < Aim.size(); i++)
        {
            Aim[i].fire = false;
        }
    }
    if (u)
    {
        eyex=0;
        eyey=5;
        eyez=0;
    }

    if (left ) {
        
        boat.rotation +=0.6;
        if((boat.flagz<1&&boat.flagz>-1)||boat.flagz>0)
        {
            boat.flagz -= 0.05;
            boat.drawFlag();
        }
        if(boat.rotation>360)
            boat.rotation-=360;
    }
    
    if (right ) {
        
        boat.rotation -=0.6;
        if((boat.flagz<1&&boat.flagz>-1)||boat.flagz<0)
        {
            boat.flagz+=0.05;
            boat.drawFlag();
        }
        if(boat.rotation<0)
            boat.rotation+=360;
       
    }
    
    if (up ) {
        //system(" afplay  ../resources/boat.wav ");
        boat.position.x -=boat.speed*(cos(boat.rotation * M_PI/180.0f));
        boat.position.z +=boat.speed*(sin(boat.rotation * M_PI/180.0f));
        int noD = 15;
        while (noD--)
        {
            int angle = rand() % 20 + 30;
            int angle2 = rand() % 20;
            if (rand() % 2 == 0)
                angle2 = -angle2;

            float speedx = -3 * cos(angle * M_PI / 180.0f) * (cos((cannon.rotation + angle2) * M_PI / 180.0f));
            float speedz = -3 * cos(angle * M_PI / 180.0f) * (sin((cannon.rotation + angle2) * M_PI / 180.0f));
            float speedy = 3 * (sin(angle * M_PI / 180.0f));
            drops.push_back(Ball(boat.position.x, boat.position.y-0.6, boat.position.z, speedx, speedy, speedz,0.05));

            //cout << drops[noDrops].size<<endl;
            drops[noDrops].fire = true;
            noDrops++;
        }

        //boat.tick();
       
    }
    if (down) {
        //system(" afplay  ../resources/boat.wav ");
        boat.position.x +=boat.speed*(cos(boat.rotation * M_PI/180.0f));
        boat.position.z -=boat.speed*(sin(boat.rotation * M_PI/180.0f));
    }
    
        
}


void tick_elements() {
    //cout<<score.score<<" "<< score.health<<endl;
    //cout<<Boss.health<<"\n";
    if (respwan_timer.processTick())
        gameTime -= 1 ;
    if (score.health > 0)

    {
        // if(seaDraw.processTick())
        // {
        //     sea.c++;
        //     sea.c = sea.c % 2;
        //     sea.drawSea();
        // }
        angle_correlate(window);
        int x = 0;
        for (int i = 0; i < noDrops; i++)
        {
            if(drops[i].position.y<-1)
            {
                drops[i].fire = false;
                drops.erase(drops.begin() + i);
                x++;

            }
            drops[i].tick1();
        }
        noDrops -= x;
        x = 0;
        for (int i = 0; i < noParts; i++)
        {
            if(parts[i].position.y<-1)
            {
                parts[i].fire = false;
                parts.erase(parts.begin() + i);
                x++;

            }
            parts[i].tick1();
        }
        noParts -= x;
        if (Boss.active)
        {
            if(bossTimer.processTick())
                system(" afplay  ../resources/boss.wav ");
            Boss.speed = 0.2;
            Boss.rotation = boat.rotation;
            Boss.rad = 4;
            Boss.side = 7;
            Boss.position.y = 9;
            Boss.tick1(boat.position.x,boat.position.z);
        }
        mnstTimer +=0.01;
        for(int i=0;i<NumMonster && !Boss.active ;i++)
        {
            if(monster[i].active)
            {
                if(mnstTimer>mnstTime)
                {
                    int x=rand()%Area;
                    int z=rand()%Area;
                    x = (rand()%2==1)?x:-x;
                    z = (rand()%2==1)?z:-z;
                    monster[i].set_position(x,5,z);
                    monster[i].rotation = rand();
                    monster[i].speed = (rand()%2==1)?0.2:-0.2;
                    //cout<<"changed!!\n\n";
                }
                monster[i].tick();
                if(abs(monster[i].position.x)>Area||abs(monster[i].position.y)>Area)
                    monster[i].speed = -monster[i].speed;
                for(int j=0;j<fireBallCnt;j++)
                    {
                        if(detect_collision(monster[i].bounding_box(),fireBall[j].bounding_box()) && fireBall[j].fire )
                        {
                            fireBall[j].fire = false;
                            if (monster[i].health > 0)
                        
                                monster[i].health -=5;
                            else
                            {
                                int noD = 30;
                                while (noD--)
                                {
                                    int angle = rand()%360;
                                    int angle2 = rand() %20;
                                    if (rand() % 2 == 0)
                                        angle2 = -angle2;

                                    float speedx = 3 * cos(angle * M_PI / 180.0f) * (cos((angle2) * M_PI / 180.0f));
                                    float speedz = 3 * cos(angle * M_PI / 180.0f) * (sin((angle2) * M_PI / 180.0f));
                                    float speedy = 3 * (sin(angle * M_PI / 180.0f));
                                    parts.push_back(Ball(monster[i].position.x, monster[i].position.y, monster[i].position.z, speedx, speedy, speedz, 0.3));

                                    //cout << drops[noDrops].size << endl;
                                    parts[noParts].fire = true;
                                    noParts++;
                                    
                                }
                                noMonsterKills++;
                                system(" afplay  ../resources/gift.wav ");
                                monster[i].active = false;
                                if(rand()%2==1)
                                    {
                                        gift[rand()%NumGift].set_position(monster[i].position.x,monster[i].position.y,monster[i].position.z);
                                    }
                                    else
                                    {   int j = rand()%NumBooster;
                                        if(booster[j].active)
                                             points[rand()%NumBonPoints].set_position(monster[i].position.x,monster[i].position.y,monster[i].position.z);
                                        else
                                        {
                                            booster[j].set_position(monster[i].position.x,monster[i].position.y,monster[i].position.z);
                                        }
                                    }
                                score.score += 10;
                            }
                        }
                    }
                
                if(detect_collision2(boat.bounding_box(),monster[i].bounding_box()) && monster[i].active)
                {
                    score.health -= 5;
                    
                    boat.position.x += 5* cos(boat.rotation*M_PI/180.0f);
                    boat.position.z -= 5* sin(boat.rotation*M_PI/180.0f);
                    boat.position.y = 10;
                    boat.jumping=true;
                    respawn();
                }
            }
        }
        if(detect_collision2(boat.bounding_box(),Boss.bounding_box())&& Boss.active)
                {
                    
                    score.health -= 15;
                    //cout<<"Collision with Boss\n";
                    boat.position.x +=2*(cos(boat.rotation * M_PI/180.0f));
                    boat.position.z -=2*(sin(boat.rotation * M_PI/180.0f));
                }
        
        if(mnstTimer>mnstTime)
            mnstTimer =0;
        
        boat.tick1();

        windD.rotation = windDirec;
        windD.position.x = boat.position.x;
        windD.position.y = boat.position.y+2;
        windD.position.z = boat.position.z;
        //cout << windD.position.x << " "<<windD.position.y<< " "<<windD.position.z<<endl;
        windD.windTimer += 0.01;
        //cout << boat.rotation<<" "<<windPresent<<"\n";
        if(windPresent && windD.windTimer <5)
        {
            
            boat.position.x -=0.03*cos(windDirec * M_PI/180.0f);
            boat.position.z +=0.03*sin(windDirec * M_PI/180.0f);
            if(windDirec<boat.rotation)
            {
                if(windDirec+0.1>boat.rotation)
                {
                    //cout <<"hello2\n";
                    boat.rotation = windDirec;

                }
                else
                    boat.rotation -=0.1;
            }
            else if (windDirec>boat.rotation)
            {
                if(windDirec-0.1<boat.rotation)
                {
                    cout <<"hello1\n";
                    boat.rotation = windDirec;
                }
                else
                    boat.rotation +=0.1;
            }

        }
        else
        {
            windD.windTimer = 0;
            windPresent = false;

        }
        //int i=0;
        for(int i=0;i<NumGift;i++)
            gift[i].tick1();
        for(int i=0;i<fireBallCnt;i++)
        {
            if(fireBall[i].fire)
            {
                fireBall[i].tick();
            }
            if(detect_collision(Boss.bounding_box(),fireBall[i].bounding_box()) && Boss.active && fireBall[i].fire)
                        {
                            fireBall[i].fire = false;
                            if (Boss.health > 0)
                                Boss.health -=5;
                            else
                            {
                                Boss.active = false;
                                score.score += 100;
                                int ng = 5;
                                while(ng--)
                                {
                                    int x=rand()%5;
                                    int z=rand()%5;
                                    x = (rand()%2==1)?x:-x;
                                    z = (rand()%2==1)?z:-z;
                                if(rand()%2==1)
                                    {
                                        gift[rand()%NumGift].set_position(monster[i].position.x+x,monster[i].position.y-5,monster[i].position.z+z);
                                    }
                                    else
                                    {   int j = rand()%NumBooster;
                                        if(booster[j].active)
                                             points[rand()%NumBonPoints].set_position(monster[i].position.x+x,monster[i].position.y-5,monster[i].position.z+z);
                                        else
                                        {
                                            booster[j].set_position(monster[i].position.x+x,monster[i].position.y-5,monster[i].position.z+z);
                                        }
                                    }
                                }
                            }
                            
                        }
        }
        cannon.position.x=boat.position.x;
        cannon.position.y=boat.position.y+2;
        cannon.position.z=boat.position.z;
        cannon.rotation = boat.rotation;
        switch(cam)
        {
            case 1:
                eyex = boat.position.x - 4.6*cos(boat.rotation*M_PI/180.0f);
                eyey = boat.position.y+1.2;
                eyez = boat.position.z+ 4.6*sin(boat.rotation*M_PI/180.0f);
                tarx = (boat.position.x) - 5*cos(boat.rotation*M_PI/180.0f);
                tary = boat.position.y+1.2;
                tarz = boat.position.z + 5*sin(boat.rotation*M_PI/180.0f);
                break;
            case 2:
                eyex = boat.position.x + 1;
                eyey = boat.position.y+20;
                eyez = boat.position.z;//+ 3.4*sin(boat.rotation*M_PI/180.0f);
                tarx = (boat.position.x);// - 4*cos(boat.rotation*M_PI/180.0f);
                tary = boat.position.y;
                tarz = boat.position.z ;//+ 4*sin(boat.rotation*M_PI/180.0f);
                break;
            case 3:
                eyex = 15;
                eyey = 15;
                eyez = 0;
                tarx = 0;
                tary = 0;
                tarz = 0;
                break;
            case 4:
            double mouse_pos_x,mouse_pos_y;
            glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);
            float angle;
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            if(right_mouse_click==1)
            {
                angle = 90-(mouse_pos_y)*90/height;
                eyey = 20*sin(angle*M_PI/180);
                tarx = boat.position.x;
                tarz = boat.position.z;
                tary = boat.position.y+5;
            }

            if(left_mouse_click==1)
            {
                angle=(mouse_pos_x)*360/width;
                eyex =boat.position.x -(20)*cos(angle*M_PI/180);
                eyez =boat.position.z +(20)*sin(angle*M_PI/180);
                tarx = boat.position.x;
                tarz = boat.position.z;
                tary = boat.position.y+5;
            }
            break;
            default:
                eyex = boat.position.x + 10*cos(boat.rotation*M_PI/180.0f);
                eyey = boat.position.y+10;
                eyez = boat.position.z - 10*sin(boat.rotation*M_PI/180.0f);
                tarx = boat.position.x - 4*cos(boat.rotation*M_PI/180.0f);
                tary = boat.position.y+3;
                tarz = boat.position.z + 4*sin(boat.rotation*M_PI/180.0f);
        }
        int i;
        for ( i=0;i<NumRock;i++)
        {
            
            if (detect_collision(boat.bounding_box(), rock[i].bounding_box()) && !rock[i].collapsed)
            {

                rock[i].noColls++;
                boat.speed = 0;
                score.health -= 3;
                cout << "Collision with rock\n";
                //rock[i].set_position(1000,1000,100);
                boat.position.x += 2 * (cos(boat.rotation * M_PI / 180.0f));
                boat.position.z -= 2 * boat.speed * (sin(boat.rotation * M_PI / 180.0f));

                break;
             }
             if (rock[i].noColls >= 5)
                 rock[i].collapsed = true;
             if (rock[i].collapsed)
                 rock[i].tick();
        }

        if(i==NumRock)
        {
            boat.speed=0.5;
        }
        for(int i=0;i<NumBooster;i++)
            {
                if(booster[i].active && detect_collision(boat.bounding_box(),booster[i].bounding_box()))
                {
                    booster[i].active = false;
                    boosterValue +=12;
                }
                if(bstr.processTick())
                {
                    int x=rand()%Area;
                    int z=rand()%Area;
                    x = (rand()%2==1)?x:-x;
                    z = (rand()%2==1)?z:-z;
                    booster[i].set_position(x,booster[i].position.y,z);
                    if(rand()%2==1)
                        monster[i].speed = 0.2;
                    else
                    monster[i].speed = -0.2;
                    monster[i].rotation = rand();
                    if(rand()%2==1)
                        monster[i].speedy = 0;
                }

            }
        for (int i=0;i<NumGift;i++)
        {
            if(detect_collision(boat.bounding_box(),gift[i].bounding_box()))
            {
                gift[i].set_position(100,1000,100);
                if(score.health<=100)
                score.health +=5;
            }
        }
        for (int i=0;i<NumBonPoints;i++)
        {
            if(detect_collision(boat.bounding_box(),points[i].bounding_box()))
                {
                    points[i].set_position(100,1000,100);
                    score.score += 4;
                }
        }
        for (int i=0;i<NumBooster;i++)
            {
                if(booster[i].active)
                    booster[i].tick();
            }
        if(boat.jumping)
        {
            boat.jumpTime += 0.01;
            if(boat.position.y >= boat.ground )
            {
                boat.Jump(boat.jumpTime);
            }
            else
            {
                    boat.jumping = false;
                    boat.jumpTime = 0;
                    
                    boat.position.y = boat.ground;
            }
        }
    }
    else
    {
            boat.destroyed = true;
            boat.tick();
        
    }
    
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    sea = Sea(0,0,COLOR_RED,Area);
    land = Land(Area, 0, Area, COLOR_RED);
    Health = Ball(0, 0, 0, 0, 0, 0, 0.3);
    boat = Boat(0, 0.1, COLOR_RED);
    cannon = Cannon(0,1,0,COLOR_RED);
    score = Score(0,100);
    Boss = Monster(0,5,0,COLOR_RED);
    Boss.health = 200;
    windD = Wind(4,2,0,COLOR_RED);
    int noDots = 1000;
    for (int i = 0; i < noDots;i++)
    {
        Aim.push_back(Ball(0, 0, 0, 0, 0, 0, 0.12));
        Aim[i].fire = false;
    }

    for (int i = 0; i < NumMonster; i++)
    {
        int x = rand() % Area;
        int z = rand() % Area;
        x = (rand() % 2 == 1) ? x : -x;
        z = (rand() % 2 == 1) ? z : -z;
        monster[i] = Monster(x, 5, z, COLOR_RED);
        monster[i].active = true;
        if (rand() % 2 == 1)
            monster[i].speed = 0.2;
        else
            monster[i].speed = -0.2;
        monster[i].rotation = rand();
        if (rand() % 2 == 1)
            monster[i].speedy = 0;
        }

    for(int i=0;i<NumRock;i++)
    {
        int x=rand()%Area;
        int z=rand()%Area;
        x = (rand()%2==1)?x:-x;
        z = (rand()%2==1)?z:-z;
        rock[i] = Rock(x,2,z,COLOR_RED);
    }
    for(int i=0;i<NumBooster;i++)
    {
        int x=rand()%Area;
        int z=rand()%Area;
        x = (rand()%2==1)?x:-x;
        z = (rand()%2==1)?z:-z;
        booster[i] = Booster(x,2,z,COLOR_RED);
        if(rand()%2==1)
            booster[i].active = true;
        else
            booster[i].active = false;

    }
    for(int i=0;i<NumGift;i++)
    {
        int x=rand()%Area;
        int z=rand()%Area;
        x = (rand()%2==1)?x:-x;
        z = (rand()%2==1)?z:-z;
        gift[i] = Gift(x,3,z,COLOR_GREEN);
        gift[i].Point = false;
    }

    for(int i=0;i<NumBonPoints;i++)
    {
        int x=rand()%Area;
        int z=rand()%Area;
        x = (rand()%2==1)?x:-x;
        z = (rand()%2==1)?z:-z;
        points[i] = Gift(x,6,z,COLOR_POINTS);
        points[i].Point = true;
    }
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("/Users/apparilalith/Documents/personal/iiith/graphics/ass2/20161038/src/Sample_GL.vert", "/Users/apparilalith/Documents/personal/iiith/graphics/ass2/20161038/src/Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

//    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
//    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
//    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
//    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {

    srand(time(0));

    int width  = 1024;
    int height = 768;

    window = initGLFW(width, height);

    initGL (window, width, height);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
//                    system("pactl -- set-sink-volume 0 50% ");
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            string Result;
            stringstream convert;
            //cout << "nonedit score:" << score << endl;
            convert << score.score;
            Result = convert.str();

            const char *one = "Score : ";
            const char *two = Result.c_str();
            const char *three = "   Health : ";
            const char *five = "  BoostValue : ";
            const char *seven = "  Active Monsters : ";
            const char *nine = "  Boss-Health : ";
            const char *eleven = "  GameTime : ";
            string Result1;
            stringstream convert1;
            convert1 << score.health;
            Result1 = convert1.str();
            string Result2;
            stringstream convert2;
            convert2 << boosterValue;
            Result2 = convert2.str();
            string Result3;
            stringstream convert3;
            convert3 << mnstActCnt;
            Result3 = convert3.str();
            string Result5;
            stringstream convert5;
            convert5 << gameTime;
            Result5 = convert5.str();
            const char *four = Result1.c_str();
            const char *six = Result2.c_str();
            const char *eight = Result3.c_str();
            const char *twelve = Result5.c_str();
            if(Boss.active)
            {
                string Result4;
                stringstream convert4;
                convert4 << Boss.health;
                Result4 = convert4.str();
                const char *ten = Result4.c_str();
                string total( string(one) + two + string(three) + four + string(five) + six + string(seven) + eight + string(nine)+ten +string(eleven)+ twelve);
                glfwSetWindowTitle(window, total.c_str());
            }
            else
            {
                string total(string(one) + two + string(three) + four + string(five) + six + string(seven) + eight + string(eleven) + twelve);
                glfwSetWindowTitle(window, total.c_str());
            }
            

            if(rand()%2==1)
                {
                    windPresent = true;
                }
            if(windPresent)
            {
                if(wind.processTick())
                    windDirec = rand()%360;

            }
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
            if((boat.position.y <boat.ground-2)||Boss.health<=0||game.processTick())
            {
                system("pkill afplay");
                break;
            }
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a,bounding_box_t  b) {

    return (abs(a.x - b.x)  < (a.length + b.side )) &&
           (abs(a.z - b.z)  < (a.width + b.side)) && abs(a.y - b.y)<(1.5);
}

bool detect_collision1(bounding_box_t a,bounding_box_t  b) {

    return (abs(a.x - b.x)  < (a.length + b.side )) &&
           (abs(a.z - b.z)  < (a.width + b.side)) && abs(a.y - b.y)<(1.5) &&(a.y-b.y>0);
}

bool detect_collision2(bounding_box_t a,bounding_box_t  b) {

    return (abs(a.x - b.x)  < (2 )) &&
           (abs(a.z - b.z)  < (2));
}

void angle_correlate(GLFWwindow *window) {
    //if(cam!=4)
    {
        glfwGetCursorPos(window, &mouse_xpos, &mouse_ypos);
        float angle = 1 - 2*mouse_ypos/1200.0;
        cannon.rotation1 = -angle*180.0/M_PI;
    }
}

void respawn() {

    boat.speedy  = 1;
    boat.speed = -1;

    respwan_timer.processTick();
    RESPWANING = true;
}
// bool detect_collision(bounding_box_t a, bounding_box_t b) {

//            if(abs(a.x - b.x)*2 < a.width + b.width)
//             {
//               //printf("x checked \n");
//                //check the Y axis
//                if(abs(a.y - b.y)*2 < a.height + b.height)
//                {
//                   //printf("y checked\n");
//                    //check the Z axis
//                    if(abs(a.z - b.z)*2 < a.length + b.length)
//                    {
//                      //printf("z checked\n");
//                       return true;
//                    }
//                }
//             }

//             return false;
// }
void reset_screen(bool ort) {
    int o = glfwGetKey(window, GLFW_KEY_O);
    cout<<o;
    if (o)
    {
        float top    = screen_center_y + 4 / screen_zoom;
        float bottom = screen_center_y - 4 / screen_zoom;
        float left   = screen_center_x - 4 / screen_zoom;
        float right  = screen_center_x + 4 / screen_zoom;
        Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
     
    }
    else
    {
        float top    = screen_center_y + 10 / screen_zoom;
        float bottom = screen_center_y - 10 / screen_zoom;
        float left   = screen_center_x - 10 / screen_zoom;
        float right  = screen_center_x + 10 / screen_zoom;
        Matrices.projection = glm::perspective(90.0f, 1.0f,0.1f,1000.0f);
        
    }
}
