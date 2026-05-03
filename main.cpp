#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <windows.h>

// ── Mode flag: true = day, false = night ──────────────────────────────────────
bool isDayMode = true;

// ── Shared animation state ────────────────────────────────────────────────────
float moveC      = 0.0f;
float moveB1     = 0.0f;
float moveB2     = 0.0f;
float moveBird   = -15.0f;
float smokeOff   = 0.0f;
float speed      = 0.02f;

// Day-only
float rayAngle   = 0.0f;

// Night-only
float moonGlow   = 0.0f;
float starTwinkle = 0.0f;
float fireflyT   = 0.0f;

void DrawAllComponents();


// ══════════════════════════════════════════════════════════════════════════════
//  DAY – PRIMITIVE HELPERS
// ══════════════════════════════════════════════════════════════════════════════

void Day_DrawPineTree(float cx, float cy, float sc)
{
    glColor3ub(62, 38, 15);
    glBegin(GL_QUADS);
        glVertex2f(cx - 0.28f*sc, cy);
        glVertex2f(cx + 0.28f*sc, cy);
        glVertex2f(cx + 0.28f*sc, cy + 2.0f*sc);
        glVertex2f(cx - 0.28f*sc, cy + 2.0f*sc);
    glEnd();
    glColor3ub(105, 68, 28);
    glBegin(GL_QUADS);
        glVertex2f(cx - 0.07f*sc, cy);
        glVertex2f(cx + 0.07f*sc, cy);
        glVertex2f(cx + 0.05f*sc, cy + 2.0f*sc);
        glVertex2f(cx - 0.05f*sc, cy + 2.0f*sc);
    glEnd();
    glColor3ub(42, 25, 8);
    glLineWidth(0.7f);
    glBegin(GL_LINES);
        glVertex2f(cx - 0.28f*sc, cy + 0.50f*sc);  glVertex2f(cx + 0.28f*sc, cy + 0.60f*sc);
        glVertex2f(cx - 0.28f*sc, cy + 1.10f*sc);  glVertex2f(cx + 0.28f*sc, cy + 1.20f*sc);
        glVertex2f(cx - 0.28f*sc, cy + 1.65f*sc);  glVertex2f(cx + 0.28f*sc, cy + 1.72f*sc);
    glEnd();
    // Tier 1
    glColor3ub(14, 72, 22);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 2.2f*sc,  cy + 0.9f*sc);
        glVertex2f(cx,             cy + 3.8f*sc);
        glVertex2f(cx + 2.2f*sc,  cy + 0.9f*sc);
    glEnd();
    glColor3ub(24, 102, 36);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 1.8f*sc,  cy + 1.3f*sc);
        glVertex2f(cx - 0.10f*sc, cy + 3.8f*sc);
        glVertex2f(cx - 0.10f*sc, cy + 1.3f*sc);
    glEnd();
    // Tier 2
    glColor3ub(20, 95, 35);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 1.72f*sc, cy + 2.7f*sc);
        glVertex2f(cx,             cy + 5.0f*sc);
        glVertex2f(cx + 1.72f*sc, cy + 2.7f*sc);
    glEnd();
    glColor3ub(35, 130, 52);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 1.30f*sc,  cy + 3.1f*sc);
        glVertex2f(cx - 0.12f*sc,  cy + 5.0f*sc);
        glVertex2f(cx - 0.12f*sc,  cy + 3.1f*sc);
    glEnd();
    // Tier 3
    glColor3ub(28, 115, 45);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 1.2f*sc,  cy + 3.9f*sc);
        glVertex2f(cx,             cy + 6.0f*sc);
        glVertex2f(cx + 1.2f*sc,  cy + 3.9f*sc);
    glEnd();
    glColor3ub(48, 152, 68);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 0.88f*sc, cy + 4.2f*sc);
        glVertex2f(cx - 0.10f*sc, cy + 6.0f*sc);
        glVertex2f(cx - 0.10f*sc, cy + 4.2f*sc);
    glEnd();
    // Tier 4
    glColor3ub(45, 142, 62);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 0.75f*sc, cy + 5.1f*sc);
        glVertex2f(cx,             cy + 6.9f*sc);
        glVertex2f(cx + 0.75f*sc, cy + 5.1f*sc);
    glEnd();
    glColor3ub(68, 182, 88);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 0.48f*sc,  cy + 5.35f*sc);
        glVertex2f(cx - 0.06f*sc,  cy + 6.9f*sc);
        glVertex2f(cx - 0.06f*sc,  cy + 5.35f*sc);
    glEnd();
    // Tip spire
    glColor3ub(82, 195, 105);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 0.26f*sc, cy + 6.5f*sc);
        glVertex2f(cx,             cy + 7.5f*sc);
        glVertex2f(cx + 0.26f*sc, cy + 6.5f*sc);
    glEnd();
}

void Day_DrawHouse(float x, float y)
{
    // Foundation slab
    glColor3ub(108, 80, 50);
    glBegin(GL_QUADS);
        glVertex2f(x-3.4f, y-0.38f); glVertex2f(x+3.4f, y-0.38f);
        glVertex2f(x+3.4f, y+0.12f); glVertex2f(x-3.4f, y+0.12f);
    glEnd();
    // Main wall
    glColor3ub(195, 152, 100);
    glBegin(GL_QUADS);
        glVertex2f(x-3.0f, y);      glVertex2f(x+3.0f, y);
        glVertex2f(x+3.0f, y+4.5f); glVertex2f(x-3.0f, y+4.5f);
    glEnd();
    glColor3ub(162, 122, 78);
    glBegin(GL_QUADS);
        glVertex2f(x+2.62f, y);      glVertex2f(x+3.0f, y);
        glVertex2f(x+3.0f,  y+4.5f); glVertex2f(x+2.62f, y+4.5f);
    glEnd();
    // Corner posts
    glColor3ub(112, 72, 28);
    glBegin(GL_QUADS);
        glVertex2f(x-3.0f,  y);      glVertex2f(x-2.68f, y);
        glVertex2f(x-2.68f, y+4.5f); glVertex2f(x-3.0f,  y+4.5f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x+2.68f, y);      glVertex2f(x+3.0f, y);
        glVertex2f(x+3.0f,  y+4.5f); glVertex2f(x+2.68f, y+4.5f);
    glEnd();
    // Wall texture
    glColor3ub(148, 112, 68);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        glVertex2f(x-3.0f, y+1.5f); glVertex2f(x+3.0f, y+1.5f);
        glVertex2f(x-3.0f, y+3.0f); glVertex2f(x+3.0f, y+3.0f);
    glEnd();
    // Thatched roof
    glColor3ub(142, 98, 22);
    glBegin(GL_QUADS);
        glVertex2f(x-3.85f, y+4.15f); glVertex2f(x+3.85f, y+4.15f);
        glVertex2f(x+3.15f, y+5.15f); glVertex2f(x-3.15f, y+5.15f);
    glEnd();
    glColor3ub(158, 112, 32);
    glBegin(GL_QUADS);
        glVertex2f(x-3.15f, y+4.95f); glVertex2f(x+3.15f, y+4.95f);
        glVertex2f(x+2.40f, y+5.90f); glVertex2f(x-2.40f, y+5.90f);
    glEnd();
    glColor3ub(172, 128, 45);
    glBegin(GL_QUADS);
        glVertex2f(x-2.4f, y+5.70f); glVertex2f(x+2.4f, y+5.70f);
        glVertex2f(x+1.6f, y+6.60f); glVertex2f(x-1.6f, y+6.60f);
    glEnd();
    glColor3ub(185, 145, 58);
    glBegin(GL_QUADS);
        glVertex2f(x-1.6f,  y+6.40f); glVertex2f(x+1.6f,  y+6.40f);
        glVertex2f(x+0.75f, y+7.10f); glVertex2f(x-0.75f, y+7.10f);
    glEnd();
    glColor3ub(198, 160, 70);
    glBegin(GL_TRIANGLES);
        glVertex2f(x-0.75f, y+6.95f);
        glVertex2f(x,        y+7.65f);
        glVertex2f(x+0.75f, y+6.95f);
    glEnd();
    // Eave shadow
    glColor3ub(90, 60, 12);
    glBegin(GL_QUADS);
        glVertex2f(x-3.90f, y+4.10f); glVertex2f(x+3.90f, y+4.10f);
        glVertex2f(x+3.90f, y+4.32f); glVertex2f(x-3.90f, y+4.32f);
    glEnd();
    // Thatch streaks
    glColor3ub(110, 75, 15);
    glLineWidth(0.7f);
    for (int i = 0; i < 7; i++) {
        float lx = x - 3.4f + i * 1.05f;
        glBegin(GL_LINES);
            glVertex2f(lx,         y+4.15f);
            glVertex2f(lx + 0.32f, y+7.10f);
        glEnd();
    }
    // Chimney
    glColor3ub(138, 82, 52);
    glBegin(GL_QUADS);
        glVertex2f(x+1.45f, y+5.40f); glVertex2f(x+2.05f, y+5.40f);
        glVertex2f(x+2.05f, y+7.62f); glVertex2f(x+1.45f, y+7.62f);
    glEnd();
    glColor3ub(108, 58, 30);
    glLineWidth(0.7f);
    glBegin(GL_LINES);
        glVertex2f(x+1.45f, y+5.95f); glVertex2f(x+2.05f, y+5.95f);
        glVertex2f(x+1.45f, y+6.50f); glVertex2f(x+2.05f, y+6.50f);
        glVertex2f(x+1.45f, y+7.05f); glVertex2f(x+2.05f, y+7.05f);
        glVertex2f(x+1.75f, y+5.40f); glVertex2f(x+1.75f, y+7.62f);
    glEnd();
    glColor3ub(82, 50, 22);
    glBegin(GL_QUADS);
        glVertex2f(x+1.32f, y+7.52f); glVertex2f(x+2.18f, y+7.52f);
        glVertex2f(x+2.18f, y+7.75f); glVertex2f(x+1.32f, y+7.75f);
    glEnd();
    // Door
    glColor3ub(82, 50, 16);
    glBegin(GL_QUADS);
        glVertex2f(x-1.05f, y);       glVertex2f(x+1.05f, y);
        glVertex2f(x+1.05f, y+2.90f); glVertex2f(x-1.05f, y+2.90f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x-1.05f, y+2.72f); glVertex2f(x+1.05f, y+2.72f);
        glVertex2f(x+1.05f, y+3.02f); glVertex2f(x-1.05f, y+3.02f);
    glEnd();
    glColor3ub(105, 68, 24);
    for (int p = 0; p < 3; p++) {
        float px = x - 0.88f + p * 0.62f;
        glBegin(GL_QUADS);
            glVertex2f(px,        y+0.12f);
            glVertex2f(px+0.50f,  y+0.12f);
            glVertex2f(px+0.50f,  y+2.68f);
            glVertex2f(px,        y+2.68f);
        glEnd();
    }
    glColor3ub(62, 38, 10);
    glLineWidth(0.8f);
    glBegin(GL_LINES);
        glVertex2f(x-0.38f, y+0.12f); glVertex2f(x-0.38f, y+2.68f);
        glVertex2f(x+0.24f, y+0.12f); glVertex2f(x+0.24f, y+2.68f);
        glVertex2f(x-1.05f, y+1.42f); glVertex2f(x+1.05f, y+1.42f);
    glEnd();
    glColor3ub(195, 148, 18);
    glPushMatrix();
        glTranslatef(x+0.62f, y+0.88f, 0.0f);
        glutSolidSphere(0.09f, 12, 12);
    glPopMatrix();
    // Left window
    glColor3ub(82, 50, 16);
    glBegin(GL_QUADS);
        glVertex2f(x-2.88f, y+1.92f); glVertex2f(x-1.12f, y+1.92f);
        glVertex2f(x-1.12f, y+3.72f); glVertex2f(x-2.88f, y+3.72f);
    glEnd();
    glColor3ub(148, 210, 242);
    glBegin(GL_QUADS);
        glVertex2f(x-2.72f, y+2.06f); glVertex2f(x-1.28f, y+2.06f);
        glVertex2f(x-1.28f, y+3.58f); glVertex2f(x-2.72f, y+3.58f);
    glEnd();
    glColor3ub(82, 50, 16);
    glLineWidth(1.8f);
    glBegin(GL_LINES);
        glVertex2f(x-2.00f, y+2.06f); glVertex2f(x-2.00f, y+3.58f);
        glVertex2f(x-2.72f, y+2.82f); glVertex2f(x-1.28f, y+2.82f);
    glEnd();
    // Right window
    glColor3ub(82, 50, 16);
    glBegin(GL_QUADS);
        glVertex2f(x+1.12f, y+1.92f); glVertex2f(x+2.88f, y+1.92f);
        glVertex2f(x+2.88f, y+3.72f); glVertex2f(x+1.12f, y+3.72f);
    glEnd();
    glColor3ub(148, 210, 242);
    glBegin(GL_QUADS);
        glVertex2f(x+1.28f, y+2.06f); glVertex2f(x+2.72f, y+2.06f);
        glVertex2f(x+2.72f, y+3.58f); glVertex2f(x+1.28f, y+3.58f);
    glEnd();
    glColor3ub(82, 50, 16);
    glLineWidth(1.8f);
    glBegin(GL_LINES);
        glVertex2f(x+2.00f, y+2.06f); glVertex2f(x+2.00f, y+3.58f);
        glVertex2f(x+1.28f, y+2.82f); glVertex2f(x+2.72f, y+2.82f);
    glEnd();
    // Porch step
    glColor3ub(128, 96, 58);
    glBegin(GL_QUADS);
        glVertex2f(x-1.5f, y-0.38f); glVertex2f(x+1.5f, y-0.38f);
        glVertex2f(x+1.5f, y+0.05f); glVertex2f(x-1.5f, y+0.05f);
    glEnd();
}

void Day_DrawFencePost(float x, float y)
{
    glColor3ub(198, 165, 112);
    glBegin(GL_QUADS);
        glVertex2f(x-0.10f, y);       glVertex2f(x+0.10f, y);
        glVertex2f(x+0.10f, y+0.82f); glVertex2f(x-0.10f, y+0.82f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f(x-0.10f, y+0.82f);
        glVertex2f(x,        y+1.02f);
        glVertex2f(x+0.10f, y+0.82f);
    glEnd();
}

void Day_DrawBush(float x, float y, float r,
                  unsigned char R, unsigned char G, unsigned char B)
{
    glColor3ub(R, G, B);
    glPushMatrix(); glTranslatef(x-r*0.45f, y,         0.0f); glutSolidSphere(r*0.7f, 18, 18); glPopMatrix();
    glPushMatrix(); glTranslatef(x+r*0.45f, y,         0.0f); glutSolidSphere(r*0.7f, 18, 18); glPopMatrix();
    glPushMatrix(); glTranslatef(x,          y+r*0.3f, 0.0f); glutSolidSphere(r*0.8f, 18, 18); glPopMatrix();
}

void Day_DrawSmoke(float cx, float baseY)
{
    for (int i = 0; i < 4; i++) {
        float t  = fmodf(smokeOff + i * 0.25f, 1.0f);
        float sx = cx + 0.28f * sinf(t * 6.28318f);
        float sy = baseY + t * 2.2f;
        float sr = 0.10f + t * 0.22f;
        unsigned char c = (unsigned char)(172 + (int)(t * 58.0f));
        glColor3ub(c, c, c);
        glPushMatrix();
            glTranslatef(sx, sy, 0.0f);
            glutSolidSphere(sr, 14, 14);
        glPopMatrix();
    }
}


// ══════════════════════════════════════════════════════════════════════════════
//  DAY – SCENE SECTIONS
// ══════════════════════════════════════════════════════════════════════════════

void Day_DrawSky()
{
    glBegin(GL_QUADS);
        glColor3ub( 22,  82, 188); glVertex2f(-12, 14); glVertex2f(38, 14);
        glColor3ub(108, 182, 248); glVertex2f( 38,  3); glVertex2f(-12,  3);
    glEnd();
}

void Day_DrawSun()
{
    glColor3ub(255, 205, 52);
    glPushMatrix(); glTranslatef(31.5f, 11.5f, 0.0f); glutSolidSphere(1.9f, 48, 48); glPopMatrix();
    glColor3ub(255, 245, 128);
    glPushMatrix(); glTranslatef(31.5f, 11.5f, 0.0f); glutSolidSphere(1.3f, 48, 48); glPopMatrix();
    glColor3ub(255, 255, 185);
    glPushMatrix(); glTranslatef(31.5f, 11.5f, 0.0f); glutSolidSphere(0.88f, 48, 48); glPopMatrix();
    glColor3ub(255, 232, 75);
    glLineWidth(2.2f);
    for (int i = 0; i < 12; i++) {
        float a = rayAngle + i * (3.14159f * 2.0f / 12.0f);
        glBegin(GL_LINES);
            glVertex2f(31.5f + 2.1f * cosf(a), 11.5f + 2.1f * sinf(a));
            glVertex2f(31.5f + 3.5f * cosf(a), 11.5f + 3.5f * sinf(a));
        glEnd();
    }
}

void Day_DrawClouds()
{
    glColor3ub(255, 255, 255);
    glPushMatrix(); glTranslatef(moveC, 0.0f, 0.0f);
    glPushMatrix(); glTranslatef( 1.0f,6.0f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef( 1.0f,7.0f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef( 2.0f,7.0f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef( 2.0f,6.0f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef( 0.0f,6.5f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef( 3.0f,6.5f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPopMatrix();
    glPushMatrix(); glTranslatef(moveC, 0.0f, 0.0f);
    glPushMatrix(); glTranslatef(15.0f,9.0f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(15.0f,8.0f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(16.0f,8.0f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(16.0f,9.0f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(14.0f,8.5f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(17.0f,8.5f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPopMatrix();
    glPushMatrix(); glTranslatef(moveC, 0.0f, 0.0f);
    glPushMatrix(); glTranslatef(22.0f,8.0f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(22.0f,7.0f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(23.0f,8.0f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(23.0f,7.0f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(24.0f,7.5f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(21.0f,7.5f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPopMatrix();
}

void Day_DrawMountains()
{
    glColor3ub(112, 148, 192);
    glBegin(GL_POLYGON);
        glVertex2f(-12, 3);    glVertex2f(-6, 10.5f);
        glVertex2f(  3, 5.0f); glVertex2f(12, 11.5f);
        glVertex2f( 22, 4.5f); glVertex2f(29,  9.5f);
        glVertex2f( 38, 5.5f); glVertex2f(38,  3);
    glEnd();
    glColor3ub(232, 242, 255);
    glBegin(GL_TRIANGLES);
        glVertex2f( -8, 9.0f);  glVertex2f(-6, 10.5f); glVertex2f(-4, 9.0f);
        glVertex2f( 10,10.1f);  glVertex2f(12, 11.5f); glVertex2f(14,10.1f);
        glVertex2f( 27, 7.8f);  glVertex2f(29,  9.5f); glVertex2f(31, 7.8f);
    glEnd();
    glColor3ub(255, 255, 255);
    glBegin(GL_TRIANGLES);
        glVertex2f(-6.35f,10.1f); glVertex2f(-6.0f,10.5f); glVertex2f(-5.65f,10.1f);
        glVertex2f(11.65f,11.0f); glVertex2f(12.0f,11.5f); glVertex2f(12.35f,11.0f);
        glVertex2f(28.68f, 9.0f); glVertex2f(29.0f, 9.5f); glVertex2f(29.32f, 9.0f);
    glEnd();
}

void Day_DrawHills()
{
    glColor3ub(52, 118, 44);
    glBegin(GL_POLYGON);
        glVertex2f(-12, 3);    glVertex2f(-5, 7.0f);
        glVertex2f(  2, 4.0f); glVertex2f(10, 7.2f);
        glVertex2f( 18, 3.9f); glVertex2f(26, 6.6f);
        glVertex2f( 38, 4.6f); glVertex2f(38, 3); glVertex2f(-12, 3);
    glEnd();
    glColor3ub(38, 112, 32);
    glBegin(GL_POLYGON);
        glVertex2f(-12, 3);    glVertex2f(-4, 6.5f);
        glVertex2f(  5, 3.5f); glVertex2f(15, 6.2f);
        glVertex2f( 25, 3.2f); glVertex2f(38, 5.5f);
        glVertex2f( 38, 3);    glVertex2f(-12, 3);
    glEnd();
    glColor3ub(62, 145, 40);
    glBegin(GL_POLYGON);
        glVertex2f(-12, 2.85f); glVertex2f(-4, 6.35f);
        glVertex2f(  5, 3.35f); glVertex2f(15, 6.05f);
        glVertex2f( 25, 3.05f); glVertex2f(38, 5.35f);
        glVertex2f( 38, 3.0f);  glVertex2f(-12, 3.0f);
    glEnd();
    glColor3ub(25, 85, 20);
    glBegin(GL_TRIANGLES);
        glVertex2f(-4.6f, 6.2f); glVertex2f(-4.0f, 6.5f); glVertex2f(-3.4f, 6.2f);
        glVertex2f(14.4f, 5.9f); glVertex2f(15.0f, 6.2f); glVertex2f(15.6f, 5.9f);
        glVertex2f(25.6f, 5.0f); glVertex2f(26.2f, 5.5f); glVertex2f(26.8f, 5.0f);
    glEnd();
}

void Day_DrawRiver()
{
    glBegin(GL_QUADS);
        glColor3ub(35,  72, 185); glVertex2f(-12,-19); glVertex2f(38,-19);
        glColor3ub(55, 102, 218); glVertex2f(38, -11); glVertex2f(-12,-11);
    glEnd();
    glColor3ub(75, 128, 232);
    glBegin(GL_QUADS);
        glVertex2f(-12,-11.55f); glVertex2f(38,-11.55f);
        glVertex2f(38, -11.0f);  glVertex2f(-12,-11.0f);
    glEnd();
    glColor3ub(80, 135, 238);
    glLineWidth(1.1f);
    for (int i = 0; i < 7; i++) {
        float wy = -11.8f - i * 1.1f;
        glBegin(GL_LINE_STRIP);
            for (float wx = -12.0f; wx <= 38.0f; wx += 0.32f)
                glVertex2f(wx, wy + 0.24f * sinf(wx * 1.3f + moveB1 * 2.5f));
        glEnd();
    }
    glColor3ub(128, 185, 255);
    glLineWidth(0.8f);
    for (int i = 0; i < 3; i++) {
        float wy = -12.8f - i * 2.2f;
        glBegin(GL_LINE_STRIP);
            for (float wx = -12.0f; wx <= 38.0f; wx += 0.5f)
                glVertex2f(wx, wy + 0.14f * sinf(wx * 0.85f - moveB1 * 1.6f));
        glEnd();
    }
}

void Day_DrawGround()
{
    glBegin(GL_POLYGON);
        glColor3ub(30, 130, 12);
        glVertex2f(90.0f,-12.5f); glVertex2f(38.0f,-12.0f);
        glVertex2f(38.0f,  3.0f); glVertex2f(-12.0f, 3.0f);
        glVertex2f(-12.0f,-11.0f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(48, 160, 28);
        glVertex2f(-12, 2.1f); glVertex2f(38, 2.6f);
        glVertex2f( 38, 3.0f); glVertex2f(-12, 3.0f);
    glEnd();
    glColor3ub(118, 88, 50);
    glBegin(GL_QUADS);
        glVertex2f(-12,-11.42f); glVertex2f(38,-11.42f);
        glVertex2f(38, -10.90f); glVertex2f(-12,-10.90f);
    glEnd();
    glColor3ub(172, 140, 88);
    glBegin(GL_QUADS);
        glVertex2f(-12,-10.90f); glVertex2f(38,-10.90f);
        glVertex2f(38, -10.30f); glVertex2f(-12,-10.30f);
    glEnd();
    glColor3ub(52, 135, 32);
    glBegin(GL_QUADS);
        glVertex2f(-12,-10.30f); glVertex2f(38,-10.30f);
        glVertex2f(38, -10.08f); glVertex2f(-12,-10.08f);
    glEnd();
    float reedX[] = {-9.5f,-6.5f,-3.2f,0.5f,3.8f,7.2f,10.5f,14.0f,17.5f,
                     21.0f,24.5f,27.8f,31.2f,34.8f};
    int reedN = 14;
    for (int i = 0; i < reedN; i++) {
        glColor3ub(55, 90, 20);
        glLineWidth(1.3f);
        glBegin(GL_LINES);
            glVertex2f(reedX[i], -11.30f);
            glVertex2f(reedX[i], -10.08f);
        glEnd();
        glColor3ub(88, 52, 16);
        glPushMatrix();
            glTranslatef(reedX[i], -10.08f, 0.0f);
            glScalef(0.07f, 0.24f, 1.0f);
            glutSolidSphere(1.0f, 8, 8);
        glPopMatrix();
    }
    glColor3ub(162, 132, 72);
    glBegin(GL_QUADS);
        glVertex2f(-2.6f, -0.2f);   glVertex2f( 0.6f, -0.2f);
        glVertex2f( 0.6f,-10.30f);  glVertex2f(-2.6f,-10.30f);
    glEnd();
}

void Day_DrawBushes()
{
    Day_DrawBush( 6.5f, -2.5f, 0.55f, 28, 118, 20);
    Day_DrawBush( 7.6f, -2.0f, 0.42f, 35, 130, 25);
    Day_DrawBush(-9.5f, -2.5f, 0.52f, 25, 112, 18);
    Day_DrawBush(35.5f, -3.0f, 0.50f, 30, 120, 22);
    Day_DrawBush(36.5f, -2.5f, 0.38f, 25, 115, 18);
}

void Day_DrawFlowers()
{
    float          fX[5] = {  5.0f,  8.2f, -8.0f,-10.5f,  4.0f };
    float          fY[5] = { -2.8f, -1.5f, -3.0f, -2.0f, -1.8f };
    unsigned char  fR[5] = { 255,  255,  200,  255,  255 };
    unsigned char  fG[5] = {  80,  218,   80,   80,  148 };
    unsigned char  fB[5] = { 120,   50,  255,  120,  255 };
    for (int i = 0; i < 5; i++) {
        glColor3ub(18, 98, 10);
        glLineWidth(1.0f);
        glBegin(GL_LINES);
            glVertex2f(fX[i], fY[i]); glVertex2f(fX[i], fY[i]+0.5f);
        glEnd();
        glColor3ub(fR[i], fG[i], fB[i]);
        glPushMatrix();
            glTranslatef(fX[i], fY[i]+0.5f, 0.0f);
            glutSolidSphere(0.18f, 10, 10);
        glPopMatrix();
    }
}

void Day_DrawAllHouses()
{
    Day_DrawHouse(-2.0f, -7.2f);
    Day_DrawHouse(11.0f, -9.2f);
    Day_DrawSmoke(-2.0f + 1.75f, -7.2f + 7.75f);
    Day_DrawSmoke(11.0f + 1.75f, -9.2f + 7.75f);
}

void Day_DrawAllTrees()
{
    Day_DrawPineTree(19.0f, -10.0f, 1.00f);
    Day_DrawPineTree(23.5f, -10.0f, 0.88f);
    Day_DrawPineTree(29.5f, -10.0f, 1.12f);
    Day_DrawPineTree(33.8f, -10.5f, 0.72f);
}

void Day_DrawFence()
{
    for (float fx = -11.5f; fx <= 36.5f; fx += 2.2f) {
        if (fx > -2.8f && fx < 0.8f) continue;
        Day_DrawFencePost(fx, -0.8f);
    }
    glColor3ub(198, 165, 112);
    glLineWidth(1.4f);
    glBegin(GL_LINES);
        glVertex2f(-11.5f, -0.15f); glVertex2f(-2.8f, -0.15f);
        glVertex2f(-11.5f, -0.45f); glVertex2f(-2.8f, -0.45f);
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(0.8f, -0.15f); glVertex2f(36.5f, -0.15f);
        glVertex2f(0.8f, -0.45f); glVertex2f(36.5f, -0.45f);
    glEnd();
}

void Day_DrawRailway()
{
    glColor3ub(155, 29, 29);
    glBegin(GL_QUADS);
        glVertex2f(-12,     2.00f); glVertex2f(38,     3.00f);
        glVertex2f(37.98f,  2.69f); glVertex2f(-11.98f,1.71f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(-12.07f, 0.72f); glVertex2f(-12.07f, 0.48f);
        glVertex2f( 38.02f, 1.52f); glVertex2f( 38.0f,  1.70f);
    glEnd();
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
        glVertex2f(-8.00f, 2.08f); glVertex2f(-7.64f, 2.08f);
        glVertex2f(-7.63f, 0.63f); glVertex2f(-8.00f, 0.62f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(0.97f, 2.31f); glVertex2f(1.28f, 2.27f);
        glVertex2f(1.34f, 0.76f); glVertex2f(0.97f, 0.75f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(11.98f, 2.48f); glVertex2f(12.48f, 2.49f);
        glVertex2f(12.50f, 1.00f); glVertex2f(11.98f, 0.98f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(18.39f, 2.69f); glVertex2f(19.16f, 2.62f);
        glVertex2f(19.18f, 1.13f); glVertex2f(18.42f, 1.11f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(25.45f, 2.75f); glVertex2f(26.09f, 2.76f);
        glVertex2f(26.09f, 1.27f); glVertex2f(25.45f, 1.26f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(33.99f, 2.92f); glVertex2f(34.48f, 2.93f);
        glVertex2f(34.58f, 1.45f); glVertex2f(34.03f, 1.44f);
    glEnd();
}

void Day_DrawBirds()
{
    glColor3ub(18, 18, 18);
    glLineWidth(1.8f);
    float bOff[5][2] = {{0.0f,9.0f},{2.8f,10.3f},{5.8f,8.7f},{8.8f,9.9f},{11.5f,9.3f}};
    for (int i = 0; i < 5; i++) {
        float bx = bOff[i][0] + moveBird;
        float by = bOff[i][1];
        if (bx > -13.0f && bx < 40.0f) {
            glBegin(GL_LINE_STRIP);
                glVertex2f(bx - 0.7f, by + 0.32f);
                glVertex2f(bx,         by);
                glVertex2f(bx + 0.7f, by + 0.32f);
            glEnd();
        }
    }
}

void Day_DrawBoats()
{
    // Boat 1
    glPushMatrix();
    glTranslatef(moveB1, 0.0f, 0.0f);
    glColor3ub(139, 69, 19);
    glBegin(GL_QUADS);
        glVertex2f( 1.0f,-14.0f); glVertex2f( 1.5f,-13.0f);
        glVertex2f(-2.0f,-13.0f); glVertex2f(-3.0f,-14.0f);
    glEnd();
    glColor3ub(0,0,0);
    glBegin(GL_QUADS);
        glVertex2f( 2.0f,-14.5f); glVertex2f( 2.0f,-14.0f);
        glVertex2f(-3.0f,-14.0f); glVertex2f(-3.0f,-14.5f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f(-3.0f,-14.5f); glVertex2f(-3.0f,-14.0f); glVertex2f(-4.5f,-13.7f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f( 2.0f,-14.5f); glVertex2f( 3.5f,-13.7f); glVertex2f( 2.0f,-14.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f( 2.0f,-14.0f); glVertex2f( 1.5f,-13.0f); glVertex2f( 1.0f,-14.0f);
    glEnd();
    glColor3ub(101, 67, 33);
    glLineWidth(2.2f);
    glBegin(GL_LINES);
        glVertex2f(-0.5f,-13.0f); glVertex2f(-0.5f,-10.2f);
    glEnd();
    glColor3ub(242, 230, 205);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f,-10.2f); glVertex2f(2.4f,-12.7f); glVertex2f(-0.5f,-13.0f);
    glEnd();
    glColor3ub(212, 200, 178);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f,-10.2f); glVertex2f(-0.5f,-13.0f); glVertex2f(-3.0f,-12.7f);
    glEnd();
    glPopMatrix();
    // Boat 2
    glPushMatrix();
    glTranslatef(moveB2, 0.0f, 0.0f);
    glColor3ub(139,69,19);
    glBegin(GL_QUADS);
        glVertex2f(22.0f,-17.5f); glVertex2f(21.0f,-16.5f);
        glVertex2f(17.5f,-16.5f); glVertex2f(18.0f,-17.5f);
    glEnd();
    glColor3ub(0,0,0);
    glBegin(GL_QUADS);
        glVertex2f(22.0f,-18.0f); glVertex2f(22.0f,-17.5f);
        glVertex2f(17.0f,-17.5f); glVertex2f(17.0f,-18.0f);
    glEnd();
    glColor3ub(255,99,71);
    glBegin(GL_QUADS);
        glVertex2f(20.5f,-16.5f); glVertex2f(21.0f,-14.5f);
        glVertex2f(18.5f,-14.5f); glVertex2f(18.0f,-16.5f);
    glEnd();
    glColor3ub(139,69,19);
    glBegin(GL_QUADS);
        glVertex2f(19.8f,-14.5f); glVertex2f(19.8f,-14.0f);
        glVertex2f(19.7f,-14.0f); glVertex2f(19.7f,-14.5f);
    glEnd();
    glColor3ub(0,0,0);
    glBegin(GL_TRIANGLES);
        glVertex2f(17.0f,-18.0f); glVertex2f(17.0f,-17.5f); glVertex2f(15.5f,-17.2f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f(22.0f,-17.5f); glVertex2f(22.0f,-18.0f); glVertex2f(23.5f,-17.2f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f(17.0f,-17.5f); glVertex2f(18.0f,-17.5f); glVertex2f(17.5f,-16.5f);
    glEnd();
    glPopMatrix();
}


// ══════════════════════════════════════════════════════════════════════════════
//  NIGHT – PRIMITIVE HELPERS
// ══════════════════════════════════════════════════════════════════════════════

void Night_DrawPineTree(float cx, float cy, float sc)
{
    glColor3ub(28, 16, 6);
    glBegin(GL_QUADS);
        glVertex2f(cx - 0.28f*sc, cy);
        glVertex2f(cx + 0.28f*sc, cy);
        glVertex2f(cx + 0.28f*sc, cy + 2.0f*sc);
        glVertex2f(cx - 0.28f*sc, cy + 2.0f*sc);
    glEnd();
    glColor3ub(50, 30, 10);
    glBegin(GL_QUADS);
        glVertex2f(cx - 0.07f*sc, cy);
        glVertex2f(cx + 0.07f*sc, cy);
        glVertex2f(cx + 0.05f*sc, cy + 2.0f*sc);
        glVertex2f(cx - 0.05f*sc, cy + 2.0f*sc);
    glEnd();
    glColor3ub(5, 28, 10);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 2.2f*sc,  cy + 0.9f*sc);
        glVertex2f(cx,             cy + 3.8f*sc);
        glVertex2f(cx + 2.2f*sc,  cy + 0.9f*sc);
    glEnd();
    glColor3ub(10, 45, 18);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 1.8f*sc,  cy + 1.3f*sc);
        glVertex2f(cx - 0.10f*sc, cy + 3.8f*sc);
        glVertex2f(cx - 0.10f*sc, cy + 1.3f*sc);
    glEnd();
    glColor3ub(8, 38, 15);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 1.72f*sc, cy + 2.7f*sc);
        glVertex2f(cx,             cy + 5.0f*sc);
        glVertex2f(cx + 1.72f*sc, cy + 2.7f*sc);
    glEnd();
    glColor3ub(15, 55, 25);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 1.30f*sc,  cy + 3.1f*sc);
        glVertex2f(cx - 0.12f*sc,  cy + 5.0f*sc);
        glVertex2f(cx - 0.12f*sc,  cy + 3.1f*sc);
    glEnd();
    glColor3ub(10, 45, 20);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 1.2f*sc,  cy + 3.9f*sc);
        glVertex2f(cx,             cy + 6.0f*sc);
        glVertex2f(cx + 1.2f*sc,  cy + 3.9f*sc);
    glEnd();
    glColor3ub(20, 65, 32);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 0.88f*sc, cy + 4.2f*sc);
        glVertex2f(cx - 0.10f*sc, cy + 6.0f*sc);
        glVertex2f(cx - 0.10f*sc, cy + 4.2f*sc);
    glEnd();
    glColor3ub(15, 58, 28);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 0.75f*sc, cy + 5.1f*sc);
        glVertex2f(cx,             cy + 6.9f*sc);
        glVertex2f(cx + 0.75f*sc, cy + 5.1f*sc);
    glEnd();
    glColor3ub(38, 90, 52);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 0.48f*sc,  cy + 5.35f*sc);
        glVertex2f(cx - 0.06f*sc,  cy + 6.9f*sc);
        glVertex2f(cx - 0.06f*sc,  cy + 5.35f*sc);
    glEnd();
    glColor3ub(45, 105, 62);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 0.26f*sc, cy + 6.5f*sc);
        glVertex2f(cx,             cy + 7.5f*sc);
        glVertex2f(cx + 0.26f*sc, cy + 6.5f*sc);
    glEnd();
}

void Night_DrawHouse(float x, float y)
{
    glColor3ub(40, 28, 16);
    glBegin(GL_QUADS);
        glVertex2f(x-3.4f, y-0.38f); glVertex2f(x+3.4f, y-0.38f);
        glVertex2f(x+3.4f, y+0.12f); glVertex2f(x-3.4f, y+0.12f);
    glEnd();
    glColor3ub(68, 48, 28);
    glBegin(GL_QUADS);
        glVertex2f(x-3.0f, y);      glVertex2f(x+3.0f, y);
        glVertex2f(x+3.0f, y+4.5f); glVertex2f(x-3.0f, y+4.5f);
    glEnd();
    glColor3ub(52, 36, 20);
    glBegin(GL_QUADS);
        glVertex2f(x+2.62f, y); glVertex2f(x+3.0f, y);
        glVertex2f(x+3.0f, y+4.5f); glVertex2f(x+2.62f, y+4.5f);
    glEnd();
    glColor3ub(35, 22, 8);
    glBegin(GL_QUADS);
        glVertex2f(x-3.0f,  y);      glVertex2f(x-2.68f, y);
        glVertex2f(x-2.68f, y+4.5f); glVertex2f(x-3.0f,  y+4.5f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x+2.68f, y);      glVertex2f(x+3.0f, y);
        glVertex2f(x+3.0f,  y+4.5f); glVertex2f(x+2.68f, y+4.5f);
    glEnd();
    glColor3ub(48, 32, 15);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        glVertex2f(x-3.0f, y+1.5f); glVertex2f(x+3.0f, y+1.5f);
        glVertex2f(x-3.0f, y+3.0f); glVertex2f(x+3.0f, y+3.0f);
    glEnd();
    // Thatched roof
    glColor3ub(48, 30, 5);
    glBegin(GL_QUADS);
        glVertex2f(x-3.85f, y+4.15f); glVertex2f(x+3.85f, y+4.15f);
        glVertex2f(x+3.15f, y+5.15f); glVertex2f(x-3.15f, y+5.15f);
    glEnd();
    glColor3ub(58, 38, 8);
    glBegin(GL_QUADS);
        glVertex2f(x-3.15f, y+4.95f); glVertex2f(x+3.15f, y+4.95f);
        glVertex2f(x+2.40f, y+5.90f); glVertex2f(x-2.40f, y+5.90f);
    glEnd();
    glColor3ub(68, 45, 10);
    glBegin(GL_QUADS);
        glVertex2f(x-2.4f, y+5.70f); glVertex2f(x+2.4f, y+5.70f);
        glVertex2f(x+1.6f, y+6.60f); glVertex2f(x-1.6f, y+6.60f);
    glEnd();
    glColor3ub(75, 50, 12);
    glBegin(GL_QUADS);
        glVertex2f(x-1.6f,  y+6.40f); glVertex2f(x+1.6f,  y+6.40f);
        glVertex2f(x+0.75f, y+7.10f); glVertex2f(x-0.75f, y+7.10f);
    glEnd();
    glColor3ub(82, 56, 15);
    glBegin(GL_TRIANGLES);
        glVertex2f(x-0.75f, y+6.95f);
        glVertex2f(x,        y+7.65f);
        glVertex2f(x+0.75f, y+6.95f);
    glEnd();
    glColor3ub(25, 15, 3);
    glBegin(GL_QUADS);
        glVertex2f(x-3.90f, y+4.10f); glVertex2f(x+3.90f, y+4.10f);
        glVertex2f(x+3.90f, y+4.32f); glVertex2f(x-3.90f, y+4.32f);
    glEnd();
    glColor3ub(35, 22, 5);
    glLineWidth(0.7f);
    for (int i = 0; i < 7; i++) {
        float lx = x - 3.4f + i * 1.05f;
        glBegin(GL_LINES);
            glVertex2f(lx,         y+4.15f);
            glVertex2f(lx + 0.32f, y+7.10f);
        glEnd();
    }
    // Chimney
    glColor3ub(55, 30, 18);
    glBegin(GL_QUADS);
        glVertex2f(x+1.45f, y+5.40f); glVertex2f(x+2.05f, y+5.40f);
        glVertex2f(x+2.05f, y+7.62f); glVertex2f(x+1.45f, y+7.62f);
    glEnd();
    glColor3ub(38, 20, 10);
    glLineWidth(0.7f);
    glBegin(GL_LINES);
        glVertex2f(x+1.45f, y+5.95f); glVertex2f(x+2.05f, y+5.95f);
        glVertex2f(x+1.45f, y+6.50f); glVertex2f(x+2.05f, y+6.50f);
        glVertex2f(x+1.45f, y+7.05f); glVertex2f(x+2.05f, y+7.05f);
        glVertex2f(x+1.75f, y+5.40f); glVertex2f(x+1.75f, y+7.62f);
    glEnd();
    glColor3ub(28, 15, 6);
    glBegin(GL_QUADS);
        glVertex2f(x+1.32f, y+7.52f); glVertex2f(x+2.18f, y+7.52f);
        glVertex2f(x+2.18f, y+7.75f); glVertex2f(x+1.32f, y+7.75f);
    glEnd();
    // Door
    glColor3ub(28, 15, 5);
    glBegin(GL_QUADS);
        glVertex2f(x-1.05f, y);       glVertex2f(x+1.05f, y);
        glVertex2f(x+1.05f, y+2.90f); glVertex2f(x-1.05f, y+2.90f);
    glEnd();
    glColor3ub(38, 22, 8);
    for (int p = 0; p < 3; p++) {
        float px = x - 0.88f + p * 0.62f;
        glBegin(GL_QUADS);
            glVertex2f(px,       y+0.12f);
            glVertex2f(px+0.50f, y+0.12f);
            glVertex2f(px+0.50f, y+2.68f);
            glVertex2f(px,       y+2.68f);
        glEnd();
    }
    glColor3ub(18, 10, 3);
    glLineWidth(0.8f);
    glBegin(GL_LINES);
        glVertex2f(x-0.38f, y+0.12f); glVertex2f(x-0.38f, y+2.68f);
        glVertex2f(x+0.24f, y+0.12f); glVertex2f(x+0.24f, y+2.68f);
        glVertex2f(x-1.05f, y+1.42f); glVertex2f(x+1.05f, y+1.42f);
    glEnd();
    glColor3ub(168, 120, 12);
    glPushMatrix();
        glTranslatef(x+0.62f, y+0.88f, 0.0f);
        glutSolidSphere(0.09f, 12, 12);
    glPopMatrix();
    // Glowing left window
    glColor3ub(80, 55, 5);
    glBegin(GL_QUADS);
        glVertex2f(x-3.05f, y+1.75f); glVertex2f(x-0.95f, y+1.75f);
        glVertex2f(x-0.95f, y+3.90f); glVertex2f(x-3.05f, y+3.90f);
    glEnd();
    glColor3ub(28, 15, 5);
    glBegin(GL_QUADS);
        glVertex2f(x-2.88f, y+1.92f); glVertex2f(x-1.12f, y+1.92f);
        glVertex2f(x-1.12f, y+3.72f); glVertex2f(x-2.88f, y+3.72f);
    glEnd();
    glColor3ub(238, 175, 42);
    glBegin(GL_QUADS);
        glVertex2f(x-2.72f, y+2.06f); glVertex2f(x-1.28f, y+2.06f);
        glVertex2f(x-1.28f, y+3.58f); glVertex2f(x-2.72f, y+3.58f);
    glEnd();
    glColor3ub(28, 15, 5);
    glLineWidth(1.8f);
    glBegin(GL_LINES);
        glVertex2f(x-2.00f, y+2.06f); glVertex2f(x-2.00f, y+3.58f);
        glVertex2f(x-2.72f, y+2.82f); glVertex2f(x-1.28f, y+2.82f);
    glEnd();
    // Glowing right window
    glColor3ub(80, 55, 5);
    glBegin(GL_QUADS);
        glVertex2f(x+0.95f, y+1.75f); glVertex2f(x+3.05f, y+1.75f);
        glVertex2f(x+3.05f, y+3.90f); glVertex2f(x+0.95f, y+3.90f);
    glEnd();
    glColor3ub(28, 15, 5);
    glBegin(GL_QUADS);
        glVertex2f(x+1.12f, y+1.92f); glVertex2f(x+2.88f, y+1.92f);
        glVertex2f(x+2.88f, y+3.72f); glVertex2f(x+1.12f, y+3.72f);
    glEnd();
    glColor3ub(228, 162, 35);
    glBegin(GL_QUADS);
        glVertex2f(x+1.28f, y+2.06f); glVertex2f(x+2.72f, y+2.06f);
        glVertex2f(x+2.72f, y+3.58f); glVertex2f(x+1.28f, y+3.58f);
    glEnd();
    glColor3ub(28, 15, 5);
    glLineWidth(1.8f);
    glBegin(GL_LINES);
        glVertex2f(x+2.00f, y+2.06f); glVertex2f(x+2.00f, y+3.58f);
        glVertex2f(x+1.28f, y+2.82f); glVertex2f(x+2.72f, y+2.82f);
    glEnd();
    // Porch step
    glColor3ub(45, 32, 16);
    glBegin(GL_QUADS);
        glVertex2f(x-1.5f, y-0.38f); glVertex2f(x+1.5f, y-0.38f);
        glVertex2f(x+1.5f, y+0.05f); glVertex2f(x-1.5f, y+0.05f);
    glEnd();
    // Hanging lantern
    glColor3ub(88, 58, 18);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        glVertex2f(x, y+4.50f); glVertex2f(x, y+4.00f);
    glEnd();
    glColor3ub(200, 130, 20);
    glPushMatrix();
        glTranslatef(x, y+3.78f, 0.0f);
        glScalef(0.18f, 0.28f, 1.0f);
        glutSolidSphere(1.0f, 14, 14);
    glPopMatrix();
    glColor3ub(255, 200, 60);
    glPushMatrix();
        glTranslatef(x, y+3.80f, 0.0f);
        glutSolidSphere(0.10f, 10, 10);
    glPopMatrix();
    glColor3ub(100, 65, 10);
    glBegin(GL_TRIANGLES);
        glVertex2f(x-0.20f, y+4.08f); glVertex2f(x, y+4.20f); glVertex2f(x+0.20f, y+4.08f);
        glVertex2f(x-0.20f, y+3.48f); glVertex2f(x, y+3.38f); glVertex2f(x+0.20f, y+3.48f);
    glEnd();
}

void Night_DrawFencePost(float x, float y)
{
    glColor3ub(82, 62, 38);
    glBegin(GL_QUADS);
        glVertex2f(x-0.10f, y);       glVertex2f(x+0.10f, y);
        glVertex2f(x+0.10f, y+0.82f); glVertex2f(x-0.10f, y+0.82f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f(x-0.10f, y+0.82f);
        glVertex2f(x,        y+1.02f);
        glVertex2f(x+0.10f, y+0.82f);
    glEnd();
}

void Night_DrawBush(float x, float y, float r,
                    unsigned char R, unsigned char G, unsigned char B)
{
    glColor3ub(R, G, B);
    glPushMatrix(); glTranslatef(x-r*0.45f, y,        0); glutSolidSphere(r*0.7f,18,18); glPopMatrix();
    glPushMatrix(); glTranslatef(x+r*0.45f, y,        0); glutSolidSphere(r*0.7f,18,18); glPopMatrix();
    glPushMatrix(); glTranslatef(x,          y+r*0.3f,0); glutSolidSphere(r*0.8f,18,18); glPopMatrix();
}

void Night_DrawSmoke(float cx, float baseY)
{
    for (int i = 0; i < 5; i++) {
        float t  = fmodf(smokeOff + i * 0.20f, 1.0f);
        float sx = cx + 0.28f * sinf(t * 6.28318f);
        float sy = baseY + t * 2.5f;
        float sr = 0.10f + t * 0.26f;
        unsigned char c = (unsigned char)(80 + (int)(t * 90.0f));
        glColor3ub(c, c, c);
        glPushMatrix();
            glTranslatef(sx, sy, 0.0f);
            glutSolidSphere(sr, 14, 14);
        glPopMatrix();
    }
}

void Night_DrawStars()
{
    float sx[] = { -8,  -5,   0,   4,   7,  10,  13,  16,  19,  22,
                   25,  28,  31,  34,  36,  -3,   2,   8,  15,  20,
                   27,  33,  -10,  5,  11,  18,  24,  30,  37,   1,
                   -6,  12,  21,  29,  35,  -2,   6,  17,  26,  32 };
    float sy[] = { 12, 10, 13,  9,  12, 11, 13,  8,  10, 12,
                    9, 11,  8,  13, 10,  7,  9, 12,  10, 13,
                   11,  9,  6,  8,  11,  7,  12,  6,  8,  10,
                    5,  9,  6,  10,  7,  11,  8,  13,  5,  11 };
    int nStars = 40;
    glPointSize(2.2f);
    for (int i = 0; i < nStars; i++) {
        float phase = sinf(starTwinkle + i * 0.72f);
        unsigned char br = (unsigned char)(165 + (int)(phase * 75));
        glColor3ub(br, br, (unsigned char)(br < 220 ? br + 30 : 255));
        glBegin(GL_POINTS);
            glVertex2f(sx[i], sy[i]);
        glEnd();
    }
    float bsx[] = {5.0f, 18.0f, 30.0f, -4.0f};
    float bsy[] = {11.5f, 12.2f, 10.8f, 8.5f};
    for (int i = 0; i < 4; i++) {
        float bright = 0.75f + 0.25f * sinf(starTwinkle * 1.3f + i * 1.5f);
        unsigned char bv = (unsigned char)(180 * bright);
        glColor3ub(bv, bv, 255);
        glLineWidth(0.9f);
        glBegin(GL_LINES);
            glVertex2f(bsx[i]-0.45f, bsy[i]);
            glVertex2f(bsx[i]+0.45f, bsy[i]);
            glVertex2f(bsx[i], bsy[i]-0.45f);
            glVertex2f(bsx[i], bsy[i]+0.45f);
        glEnd();
    }
}

void Night_DrawFireflies()
{
    float fxBase[] = { 5.5f, 7.2f, -8.0f, -10.0f, 3.8f, 9.0f, -7.2f };
    float fyBase[] = {-2.2f,-1.8f, -2.5f,  -2.0f,-1.5f,-2.8f, -1.6f };
    int nFF = 7;
    for (int i = 0; i < nFF; i++) {
        float t = fireflyT + i * 0.87f;
        float fx = fxBase[i] + 0.6f * sinf(t * 1.1f);
        float fy = fyBase[i] + 0.4f * cosf(t * 0.8f);
        float glow = 0.5f + 0.5f * sinf(t * 2.3f);
        unsigned char G = (unsigned char)(180 * glow);
        unsigned char Y = (unsigned char)(220 * glow);
        glColor3ub(Y/4, G/4, 0);
        glPushMatrix(); glTranslatef(fx, fy, 0); glutSolidSphere(0.14f, 8, 8); glPopMatrix();
        glColor3ub(Y, G, 40);
        glPushMatrix(); glTranslatef(fx, fy, 0); glutSolidSphere(0.06f, 8, 8); glPopMatrix();
    }
}


// ══════════════════════════════════════════════════════════════════════════════
//  NIGHT – SCENE SECTIONS
// ══════════════════════════════════════════════════════════════════════════════

void Night_DrawSky()
{
    glBegin(GL_QUADS);
        glColor3ub( 2,  4, 18); glVertex2f(-12, 14); glVertex2f(38, 14);
        glColor3ub(12, 22, 68); glVertex2f( 38,  3); glVertex2f(-12,  3);
    glEnd();
}

void Night_DrawMoon()
{
    float glowPulse = 0.5f + 0.5f * sinf(moonGlow);
    unsigned char h1 = (unsigned char)(18 + 12 * glowPulse);
    glColor3ub(h1, h1, (unsigned char)(h1 * 2));
    glPushMatrix(); glTranslatef(31.5f, 11.5f, 0.0f); glutSolidSphere(3.8f, 48, 48); glPopMatrix();
    unsigned char h2 = (unsigned char)(35 + 20 * glowPulse);
    glColor3ub(h2, h2, (unsigned char)(h2 + 30));
    glPushMatrix(); glTranslatef(31.5f, 11.5f, 0.0f); glutSolidSphere(2.6f, 48, 48); glPopMatrix();
    glColor3ub(225, 228, 245);
    glPushMatrix(); glTranslatef(31.5f, 11.5f, 0.0f); glutSolidSphere(1.65f, 48, 48); glPopMatrix();
    glColor3ub(195, 198, 222);
    glPushMatrix(); glTranslatef(31.0f, 11.9f, 0.0f); glutSolidSphere(0.55f, 20, 20); glPopMatrix();
    glPushMatrix(); glTranslatef(32.1f, 11.0f, 0.0f); glutSolidSphere(0.35f, 20, 20); glPopMatrix();
    glColor3ub(10, 18, 52);
    glPushMatrix(); glTranslatef(31.9f, 11.5f, 0.0f); glutSolidSphere(1.28f, 48, 48); glPopMatrix();
}

void Night_DrawClouds()
{
    glColor3ub(30, 38, 72);
    glPushMatrix(); glTranslatef(moveC, 0.0f, 0.0f);
    glPushMatrix(); glTranslatef( 1.0f,6.0f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef( 1.0f,7.0f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef( 2.0f,7.0f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef( 2.0f,6.0f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef( 0.0f,6.5f,0); glutSolidSphere(0.7f,30,30); glPopName(); glPopMatrix();
    glPushMatrix(); glTranslatef( 3.0f,6.5f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPopMatrix();
    glColor3ub(22, 30, 62);
    glPushMatrix(); glTranslatef(moveC, 0.0f, 0.0f);
    glPushMatrix(); glTranslatef(15.0f,9.0f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(15.0f,8.0f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(16.0f,8.0f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(16.0f,9.0f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(14.0f,8.5f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(17.0f,8.5f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPopMatrix();
    glColor3ub(26, 34, 68);
    glPushMatrix(); glTranslatef(moveC, 0.0f, 0.0f);
    glPushMatrix(); glTranslatef(22.0f,8.0f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(22.0f,7.0f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(23.0f,8.0f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(23.0f,7.0f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(24.0f,7.5f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(21.0f,7.5f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPopMatrix();
}

void Night_DrawMountains()
{
    glColor3ub(28, 38, 62);
    glBegin(GL_POLYGON);
        glVertex2f(-12, 3);    glVertex2f(-6, 10.5f);
        glVertex2f(  3, 5.0f); glVertex2f(12, 11.5f);
        glVertex2f( 22, 4.5f); glVertex2f(29,  9.5f);
        glVertex2f( 38, 5.5f); glVertex2f(38,  3);
    glEnd();
    glColor3ub(188, 198, 228);
    glBegin(GL_TRIANGLES);
        glVertex2f( -8, 9.0f);  glVertex2f(-6, 10.5f); glVertex2f(-4, 9.0f);
        glVertex2f( 10,10.1f);  glVertex2f(12, 11.5f); glVertex2f(14,10.1f);
        glVertex2f( 27, 7.8f);  glVertex2f(29,  9.5f); glVertex2f(31, 7.8f);
    glEnd();
    glColor3ub(230, 238, 255);
    glBegin(GL_TRIANGLES);
        glVertex2f(-6.35f,10.1f); glVertex2f(-6.0f,10.5f); glVertex2f(-5.65f,10.1f);
        glVertex2f(11.65f,11.0f); glVertex2f(12.0f,11.5f); glVertex2f(12.35f,11.0f);
        glVertex2f(28.68f, 9.0f); glVertex2f(29.0f, 9.5f); glVertex2f(29.32f, 9.0f);
    glEnd();
}

void Night_DrawHills()
{
    glColor3ub(10, 32, 8);
    glBegin(GL_POLYGON);
        glVertex2f(-12, 3);    glVertex2f(-5, 7.0f);
        glVertex2f(  2, 4.0f); glVertex2f(10, 7.2f);
        glVertex2f( 18, 3.9f); glVertex2f(26, 6.6f);
        glVertex2f( 38, 4.6f); glVertex2f(38, 3); glVertex2f(-12, 3);
    glEnd();
    glColor3ub(8, 28, 6);
    glBegin(GL_POLYGON);
        glVertex2f(-12, 3);    glVertex2f(-4, 6.5f);
        glVertex2f(  5, 3.5f); glVertex2f(15, 6.2f);
        glVertex2f( 25, 3.2f); glVertex2f(38, 5.5f);
        glVertex2f( 38, 3);    glVertex2f(-12, 3);
    glEnd();
    glColor3ub(18, 48, 14);
    glBegin(GL_POLYGON);
        glVertex2f(-12, 2.85f); glVertex2f(-4, 6.35f);
        glVertex2f(  5, 3.35f); glVertex2f(15, 6.05f);
        glVertex2f( 25, 3.05f); glVertex2f(38, 5.35f);
        glVertex2f( 38, 3.0f);  glVertex2f(-12, 3.0f);
    glEnd();
    glColor3ub(12, 38, 10);
    glBegin(GL_TRIANGLES);
        glVertex2f(-4.6f, 6.2f); glVertex2f(-4.0f, 6.5f); glVertex2f(-3.4f, 6.2f);
        glVertex2f(14.4f, 5.9f); glVertex2f(15.0f, 6.2f); glVertex2f(15.6f, 5.9f);
        glVertex2f(25.6f, 5.0f); glVertex2f(26.2f, 5.5f); glVertex2f(26.8f, 5.0f);
    glEnd();
}

void Night_DrawRiver()
{
    glBegin(GL_QUADS);
        glColor3ub(8,  20, 68); glVertex2f(-12,-19); glVertex2f(38,-19);
        glColor3ub(15, 35, 92); glVertex2f(38, -11); glVertex2f(-12,-11);
    glEnd();
    glColor3ub(18, 42, 105);
    glBegin(GL_QUADS);
        glVertex2f(-12,-11.55f); glVertex2f(38,-11.55f);
        glVertex2f(38, -11.0f);  glVertex2f(-12,-11.0f);
    glEnd();
    // Moonlight reflection – smooth gradient, animates with waves
    {
        float moonCX = 31.5f;
        float halfW  = 3.2f;
        int   slices = 80;
        for (int s = 0; s < slices; s++) {
            float y0    = -19.0f + s       * (8.0f / slices);
            float y1    = -19.0f + (s + 1) * (8.0f / slices);
            float waver = 1.0f + 0.08f * sinf(s * 0.55f + moveB1 * 2.0f);
            float w     = halfW * waver;
            float cw    = 0.38f * waver;
            glBegin(GL_QUADS);
                glColor3ub(18, 28, 72);
                glVertex2f(moonCX - w, y0);
                glVertex2f(moonCX - w, y1);
                glColor3ub(90, 108, 168);
                glVertex2f(moonCX,     y1);
                glVertex2f(moonCX,     y0);
            glEnd();
            glBegin(GL_QUADS);
                glColor3ub(90, 108, 168);
                glVertex2f(moonCX,     y0);
                glVertex2f(moonCX,     y1);
                glColor3ub(18, 28, 72);
                glVertex2f(moonCX + w, y1);
                glVertex2f(moonCX + w, y0);
            glEnd();
            glBegin(GL_QUADS);
                glColor3ub(150, 168, 220);
                glVertex2f(moonCX - cw, y0);
                glVertex2f(moonCX - cw, y1);
                glVertex2f(moonCX + cw, y1);
                glVertex2f(moonCX + cw, y0);
            glEnd();
        }
    }
    glColor3ub(22, 48, 108);
    glLineWidth(1.0f);
    for (int i = 0; i < 7; i++) {
        float wy = -11.8f - i * 1.1f;
        glBegin(GL_LINE_STRIP);
            for (float wx = -12.0f; wx <= 38.0f; wx += 0.32f)
                glVertex2f(wx, wy + 0.24f * sinf(wx * 1.3f + moveB1 * 2.5f));
        glEnd();
    }
    glColor3ub(55, 78, 148);
    glLineWidth(0.8f);
    for (int i = 0; i < 3; i++) {
        float wy = -12.8f - i * 2.2f;
        glBegin(GL_LINE_STRIP);
            for (float wx = -12.0f; wx <= 38.0f; wx += 0.5f)
                glVertex2f(wx, wy + 0.14f * sinf(wx * 0.85f - moveB1 * 1.6f));
        glEnd();
    }
}

void Night_DrawGround()
{
    glBegin(GL_POLYGON);
        glColor3ub(8, 40, 5);
        glVertex2f(90.0f,-12.5f); glVertex2f(38.0f,-12.0f);
        glVertex2f(38.0f,  3.0f); glVertex2f(-12.0f, 3.0f);
        glVertex2f(-12.0f,-11.0f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(14, 58, 8);
        glVertex2f(-12, 2.1f); glVertex2f(38, 2.6f);
        glVertex2f( 38, 3.0f); glVertex2f(-12, 3.0f);
    glEnd();
    glColor3ub(42, 28, 12);
    glBegin(GL_QUADS);
        glVertex2f(-12,-11.42f); glVertex2f(38,-11.42f);
        glVertex2f(38, -10.90f); glVertex2f(-12,-10.90f);
    glEnd();
    glColor3ub(62, 46, 22);
    glBegin(GL_QUADS);
        glVertex2f(-12,-10.90f); glVertex2f(38,-10.90f);
        glVertex2f(38, -10.30f); glVertex2f(-12,-10.30f);
    glEnd();
    glColor3ub(14, 42, 8);
    glBegin(GL_QUADS);
        glVertex2f(-12,-10.30f); glVertex2f(38,-10.30f);
        glVertex2f(38, -10.08f); glVertex2f(-12,-10.08f);
    glEnd();
    float reedX[] = {-9.5f,-6.5f,-3.2f,0.5f,3.8f,7.2f,10.5f,14.0f,17.5f,
                     21.0f,24.5f,27.8f,31.2f,34.8f};
    int reedN = 14;
    for (int i = 0; i < reedN; i++) {
        glColor3ub(22, 40, 8);
        glLineWidth(1.3f);
        glBegin(GL_LINES);
            glVertex2f(reedX[i], -11.30f);
            glVertex2f(reedX[i], -10.08f);
        glEnd();
        glColor3ub(45, 25, 6);
        glPushMatrix();
            glTranslatef(reedX[i], -10.08f, 0.0f);
            glScalef(0.07f, 0.24f, 1.0f);
            glutSolidSphere(1.0f, 8, 8);
        glPopMatrix();
    }
    glColor3ub(55, 40, 18);
    glBegin(GL_QUADS);
        glVertex2f(-2.6f, -0.2f);   glVertex2f( 0.6f, -0.2f);
        glVertex2f( 0.6f,-10.30f);  glVertex2f(-2.6f,-10.30f);
    glEnd();
}

void Night_DrawBushes()
{
    Night_DrawBush( 6.5f, -2.5f, 0.55f,  8, 42,  6);
    Night_DrawBush( 7.6f, -2.0f, 0.42f, 10, 48,  8);
    Night_DrawBush(-9.5f, -2.5f, 0.52f,  8, 38,  5);
    Night_DrawBush(35.5f, -3.0f, 0.50f,  9, 40,  7);
    Night_DrawBush(36.5f, -2.5f, 0.38f,  8, 36,  5);
}

void Night_DrawFlowers()
{
    float          fX[5] = {  5.0f,  8.2f, -8.0f,-10.5f,  4.0f };
    float          fY[5] = { -2.8f, -1.5f, -3.0f, -2.0f, -1.8f };
    unsigned char  fR[5] = { 80,  80,  60,  80,  80 };
    unsigned char  fG[5] = { 20,  65,  20,  20,  42 };
    unsigned char  fB[5] = { 35,  12,  80,  35,  80 };
    for (int i = 0; i < 5; i++) {
        glColor3ub(5, 30, 4);
        glLineWidth(1.0f);
        glBegin(GL_LINES);
            glVertex2f(fX[i], fY[i]); glVertex2f(fX[i], fY[i]+0.5f);
        glEnd();
        glColor3ub(fR[i], fG[i], fB[i]);
        glPushMatrix();
            glTranslatef(fX[i], fY[i]+0.5f, 0.0f);
            glutSolidSphere(0.18f, 10, 10);
        glPopMatrix();
    }
}

void Night_DrawAllHouses()
{
    Night_DrawHouse(-2.0f, -7.2f);
    Night_DrawHouse(11.0f, -9.2f);
    Night_DrawSmoke(-2.0f + 1.75f, -7.2f + 7.75f);
    Night_DrawSmoke(11.0f + 1.75f, -9.2f + 7.75f);
}

void Night_DrawAllTrees()
{
    Night_DrawPineTree(19.0f, -10.0f, 1.00f);
    Night_DrawPineTree(23.5f, -10.0f, 0.88f);
    Night_DrawPineTree(29.5f, -10.0f, 1.12f);
    Night_DrawPineTree(33.8f, -10.5f, 0.72f);
}

void Night_DrawFence()
{
    for (float fx = -11.5f; fx <= 36.5f; fx += 2.2f) {
        if (fx > -2.8f && fx < 0.8f) continue;
        Night_DrawFencePost(fx, -0.8f);
    }
    glColor3ub(82, 62, 38);
    glLineWidth(1.4f);
    glBegin(GL_LINES);
        glVertex2f(-11.5f, -0.15f); glVertex2f(-2.8f, -0.15f);
        glVertex2f(-11.5f, -0.45f); glVertex2f(-2.8f, -0.45f);
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(0.8f, -0.15f); glVertex2f(36.5f, -0.15f);
        glVertex2f(0.8f, -0.45f); glVertex2f(36.5f, -0.45f);
    glEnd();
}

void Night_DrawRailway()
{
    glColor3ub(68, 12, 12);
    glBegin(GL_QUADS);
        glVertex2f(-12,     2.00f); glVertex2f(38,     3.00f);
        glVertex2f(37.98f,  2.69f); glVertex2f(-11.98f,1.71f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(-12.07f, 0.72f); glVertex2f(-12.07f, 0.48f);
        glVertex2f( 38.02f, 1.52f); glVertex2f( 38.0f,  1.70f);
    glEnd();
    glColor3ub(18, 18, 18);
    glBegin(GL_QUADS);
        glVertex2f(-8.00f, 2.08f); glVertex2f(-7.64f, 2.08f);
        glVertex2f(-7.63f, 0.63f); glVertex2f(-8.00f, 0.62f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(0.97f, 2.31f); glVertex2f(1.28f, 2.27f);
        glVertex2f(1.34f, 0.76f); glVertex2f(0.97f, 0.75f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(11.98f, 2.48f); glVertex2f(12.48f, 2.49f);
        glVertex2f(12.50f, 1.00f); glVertex2f(11.98f, 0.98f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(18.39f, 2.69f); glVertex2f(19.16f, 2.62f);
        glVertex2f(19.18f, 1.13f); glVertex2f(18.42f, 1.11f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(25.45f, 2.75f); glVertex2f(26.09f, 2.76f);
        glVertex2f(26.09f, 1.27f); glVertex2f(25.45f, 1.26f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(33.99f, 2.92f); glVertex2f(34.48f, 2.93f);
        glVertex2f(34.58f, 1.45f); glVertex2f(34.03f, 1.44f);
    glEnd();
}

void Night_DrawBirds()
{
    glColor3ub(8, 8, 22);
    glLineWidth(1.6f);
    float bOff[5][2] = {{0.0f,9.0f},{2.8f,10.3f},{5.8f,8.7f},{8.8f,9.9f},{11.5f,9.3f}};
    for (int i = 0; i < 5; i++) {
        float bx = bOff[i][0] + moveBird;
        float by = bOff[i][1];
        if (bx > -13.0f && bx < 40.0f) {
            glBegin(GL_LINE_STRIP);
                glVertex2f(bx - 0.7f, by + 0.32f);
                glVertex2f(bx,         by);
                glVertex2f(bx + 0.7f, by + 0.32f);
            glEnd();
        }
    }
}

void Night_DrawBoats()
{
    // Boat 1
    glPushMatrix();
    glTranslatef(moveB1, 0.0f, 0.0f);
    glColor3ub(55, 28, 8);
    glBegin(GL_QUADS);
        glVertex2f( 1.0f,-14.0f); glVertex2f( 1.5f,-13.0f);
        glVertex2f(-2.0f,-13.0f); glVertex2f(-3.0f,-14.0f);
    glEnd();
    glColor3ub(12, 12, 12);
    glBegin(GL_QUADS);
        glVertex2f( 2.0f,-14.5f); glVertex2f( 2.0f,-14.0f);
        glVertex2f(-3.0f,-14.0f); glVertex2f(-3.0f,-14.5f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f(-3.0f,-14.5f); glVertex2f(-3.0f,-14.0f); glVertex2f(-4.5f,-13.7f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f( 2.0f,-14.5f); glVertex2f( 3.5f,-13.7f); glVertex2f( 2.0f,-14.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f( 2.0f,-14.0f); glVertex2f( 1.5f,-13.0f); glVertex2f( 1.0f,-14.0f);
    glEnd();
    glColor3ub(45, 28, 10);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.5f,-13.0f); glVertex2f(-0.5f,-10.2f);
    glEnd();
    glColor3ub(175, 180, 210);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f,-10.2f); glVertex2f(2.4f,-12.7f); glVertex2f(-0.5f,-13.0f);
    glEnd();
    glColor3ub(140, 145, 178);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f,-10.2f); glVertex2f(-0.5f,-13.0f); glVertex2f(-3.0f,-12.7f);
    glEnd();
    glPopMatrix();
    // Boat 2
    glPushMatrix();
    glTranslatef(moveB2, 0.0f, 0.0f);
    glColor3ub(55, 28, 8);
    glBegin(GL_QUADS);
        glVertex2f(22.0f,-17.5f); glVertex2f(21.0f,-16.5f);
        glVertex2f(17.5f,-16.5f); glVertex2f(18.0f,-17.5f);
    glEnd();
    glColor3ub(12, 12, 12);
    glBegin(GL_QUADS);
        glVertex2f(22.0f,-18.0f); glVertex2f(22.0f,-17.5f);
        glVertex2f(17.0f,-17.5f); glVertex2f(17.0f,-18.0f);
    glEnd();
    glColor3ub(180, 110, 18);
    glBegin(GL_QUADS);
        glVertex2f(20.5f,-16.5f); glVertex2f(21.0f,-14.5f);
        glVertex2f(18.5f,-14.5f); glVertex2f(18.0f,-16.5f);
    glEnd();
    glColor3ub(255, 195, 55);
    glBegin(GL_QUADS);
        glVertex2f(19.0f,-16.0f); glVertex2f(20.5f,-16.0f);
        glVertex2f(20.5f,-15.0f); glVertex2f(19.0f,-15.0f);
    glEnd();
    glColor3ub(55, 28, 8);
    glBegin(GL_QUADS);
        glVertex2f(19.8f,-14.5f); glVertex2f(19.8f,-14.0f);
        glVertex2f(19.7f,-14.0f); glVertex2f(19.7f,-14.5f);
    glEnd();
    glColor3ub(12, 12, 12);
    glBegin(GL_TRIANGLES);
        glVertex2f(17.0f,-18.0f); glVertex2f(17.0f,-17.5f); glVertex2f(15.5f,-17.2f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f(22.0f,-17.5f); glVertex2f(22.0f,-18.0f); glVertex2f(23.5f,-17.2f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f(17.0f,-17.5f); glVertex2f(18.0f,-17.5f); glVertex2f(17.5f,-16.5f);
    glEnd();
    glPopMatrix();
}


// ══════════════════════════════════════════════════════════════════════════════
//  MASTER DRAW – dispatches to day or night set
// ══════════════════════════════════════════════════════════════════════════════
void DrawAllComponents()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-12, 38, -19, 14);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (isDayMode) {
        Day_DrawSky();
        Day_DrawSun();
        Day_DrawClouds();
        Day_DrawMountains();
        Day_DrawHills();
        Day_DrawRiver();
        Day_DrawGround();
        Day_DrawBushes();
        Day_DrawFlowers();
        Day_DrawAllHouses();
        Day_DrawAllTrees();
        Day_DrawFence();
        Day_DrawRailway();
        Day_DrawBirds();
        Day_DrawBoats();
    } else {
        Night_DrawSky();
        Night_DrawStars();
        Night_DrawMoon();
        Night_DrawClouds();
        Night_DrawMountains();
        Night_DrawHills();
        Night_DrawRiver();
        Night_DrawGround();
        Night_DrawBushes();
        Night_DrawFlowers();
        Night_DrawFireflies();
        Night_DrawAllHouses();
        Night_DrawAllTrees();
        Night_DrawFence();
        Night_DrawRailway();
        Night_DrawBirds();
        Night_DrawBoats();
    }

    glutSwapBuffers();
}


// ══════════════════════════════════════════════════════════════════════════════
//  TIMER CALLBACKS
// ══════════════════════════════════════════════════════════════════════════════
void updateC(int v)
{
    moveC = (moveC > 36.0f) ? -38.0f : moveC + 0.13f;
    glutTimerFunc(20, updateC, 0);
    glutPostRedisplay();
}

void updateB1(int v)
{
    moveB1 += speed;
    if (moveB1 > 38.0f) moveB1 = -38.0f;
    glutTimerFunc(20, updateB1, 0);
    glutPostRedisplay();
}

void updateB2(int v)
{
    if (moveB2 < -36.0f) moveB2 = 38.0f;
    moveB2 -= 0.10f;
    glutTimerFunc(20, updateB2, 0);
    glutPostRedisplay();
}

void updateExtras(int v)
{
    moveBird += (isDayMode ? 0.08f : 0.06f);
    if (moveBird > 52.0f) moveBird = -26.0f;
    smokeOff     = fmodf(smokeOff + 0.007f, 1.0f);
    rayAngle    += 0.004f;          // day: sun rays
    moonGlow    += 0.018f;          // night: moon pulse
    starTwinkle += 0.025f;          // night: star shimmer
    fireflyT    += 0.040f;          // night: fireflies
    glutTimerFunc(30, updateExtras, 0);
    glutPostRedisplay();
}


// ══════════════════════════════════════════════════════════════════════════════
//  INPUT
// ══════════════════════════════════════════════════════════════════════════════
void handleKeypress(unsigned char key, int x, int y)
{
    if      (key == 'd' || key == 'D') { isDayMode = true;  glutPostRedisplay(); }
    else if (key == 'n' || key == 'N') { isDayMode = false; glutPostRedisplay(); }
    else if (key == 's')               { speed = 0.0f; }
    else if (key == 'r')               { speed = 0.02f; }
    glutPostRedisplay();
}

void handleMouse(int button, int state, int x, int y)
{
    if      (button == GLUT_LEFT_BUTTON)  speed += 0.05f;
    else if (button == GLUT_RIGHT_BUTTON) speed -= 0.05f;
    glutPostRedisplay();
}


// ══════════════════════════════════════════════════════════════════════════════
//  ENTRY
// ══════════════════════════════════════════════════════════════════════════════
void display(void) { DrawAllComponents(); }

void init()
{
    // Start in day mode background colour
    glClearColor(0.42f, 0.71f, 0.98f, 1.0f);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1300, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(" Village Scene  [D] Day  [N] Night ");
    init();

    glutTimerFunc(100, updateC,      1);
    glutTimerFunc(100, updateB1,     0);
    glutTimerFunc(100, updateB2,     0);
    glutTimerFunc(100, updateExtras, 0);

    glutKeyboardFunc(handleKeypress);
    glutMouseFunc(handleMouse);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
