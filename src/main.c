#include <box2d/box2d.h>
#include <raylib.h>
#include <stdio.h>

const uint32_t PIXELS_PER_METER = 16.0f;

const int screenWidth = 1280;
const int screenHeight = 720;

Vector2 worldToScreen(b2Vec2 p) {
  return (Vector2){screenWidth / 2.0f + p.x * PIXELS_PER_METER,
                   screenHeight / 2.0f - p.y * PIXELS_PER_METER};
}

int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  b2WorldDef worldDef = b2DefaultWorldDef();
  worldDef.gravity = (b2Vec2){0.0f, -10.0f};

  b2WorldId worldId = b2CreateWorld(&worldDef);

  b2BodyDef groundBodyDef = b2DefaultBodyDef();
  groundBodyDef.position = (b2Vec2){0.0f, -10.0f};

  b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);
  b2Polygon groundBox = b2MakeBox(10.0f, 1.0f);

  b2ShapeDef groundShapeDef = b2DefaultShapeDef();
  b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = b2_dynamicBody;
  bodyDef.position = (b2Vec2){0.0f, 0.0f};
  b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

  b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);

  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.density = 1.0f;
  shapeDef.material.friction = 0.3f;

  b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

  float timeStep = 1.0f / 60.0f;
  int subStepCount = 4;
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20,
             LIGHTGRAY);

    Vector2 ballPosition = worldToScreen(b2Body_GetPosition(bodyId));
    DrawCircle(ballPosition.x, ballPosition.y, 10, BLUE);

    Vector2 recPosition = worldToScreen(b2Body_GetPosition(groundId));

    DrawRectangle(recPosition.x, recPosition.y, 10.0f * PIXELS_PER_METER,
                  1.0f * PIXELS_PER_METER, RED);

    EndDrawing();

    b2World_Step(worldId, timeStep, subStepCount);
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
