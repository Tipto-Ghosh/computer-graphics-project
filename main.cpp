// ═══════════════════════════════════════════════════════════════════════════════
//   Village Scenery  –  Enhanced Edition
//   Controls : s = stop boat | r = resume boat
//              Left-click = speed up | Right-click = slow down
// ═══════════════════════════════════════════════════════════════════════════════

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <windows.h>

// ── Animation globals ────────────────────────────────────────────────────────
float moveC    = 0.0f;          // cloud drift
float moveB1   = 0.0f;          // boat 1  (left → right)
float moveB2   = 0.0f;          // boat 2  (right → left)
float moveBird = -15.0f;        // bird flock
float smokeOff = 0.0f;          // chimney smoke cycle  [0,1)
float rayAngle = 0.0f;          // slowly rotating sun rays
float speed    = 0.02f;         // boat-1 speed (keyboard / mouse)

// ── 3-tier layered pine tree ─────────────────────────────────────────────────
void DrawPineTree(float cx, float cy, float sc)
{
    // Trunk
    glColor3ub(101, 67, 33);
    glBegin(GL_QUADS);
        glVertex2f(cx - 0.35f*sc, cy);
        glVertex2f(cx + 0.35f*sc, cy);
        glVertex2f(cx + 0.35f*sc, cy + 1.8f*sc);
        glVertex2f(cx - 0.35f*sc, cy + 1.8f*sc);
    glEnd();

    // Tier 1 – bottom, darkest
    glColor3ub(18, 95, 32);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 2.0f*sc, cy + 1.0f*sc);
        glVertex2f(cx,            cy + 3.7f*sc);
        glVertex2f(cx + 2.0f*sc, cy + 1.0f*sc);
    glEnd();

    // Tier 2 – middle
    glColor3ub(30, 130, 48);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 1.55f*sc, cy + 2.7f*sc);
        glVertex2f(cx,             cy + 4.8f*sc);
        glVertex2f(cx + 1.55f*sc, cy + 2.7f*sc);
    glEnd();

    // Tier 3 – top, brightest
    glColor3ub(55, 168, 75);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 1.05f*sc, cy + 3.9f*sc);
        glVertex2f(cx,             cy + 5.8f*sc);
        glVertex2f(cx + 1.05f*sc, cy + 3.9f*sc);
    glEnd();
}

// ── Cottage house ────────────────────────────────────────────────────────────
void DrawHouse(float x, float y)
{
    // Foundation slab
    glColor3ub(125, 105, 78);
    glBegin(GL_QUADS);
        glVertex2f(x-3.3f, y-0.25f); glVertex2f(x+3.3f, y-0.25f);
        glVertex2f(x+3.3f, y+0.05f); glVertex2f(x-3.3f, y+0.05f);
    glEnd();

    // Main wall
    glColor3ub(238, 215, 168);
    glBegin(GL_QUADS);
        glVertex2f(x-3.0f, y);      glVertex2f(x+3.0f, y);
        glVertex2f(x+3.0f, y+4.5f); glVertex2f(x-3.0f, y+4.5f);
    glEnd();

    // Right shadow strip on wall
    glColor3ub(195, 178, 135);
    glBegin(GL_QUADS);
        glVertex2f(x+2.65f, y);      glVertex2f(x+3.0f, y);
        glVertex2f(x+3.0f,  y+4.5f); glVertex2f(x+2.65f, y+4.5f);
    glEnd();

    // Roof (left half – lighter)
    glColor3ub(168, 38, 38);
    glBegin(GL_TRIANGLES);
        glVertex2f(x-3.65f, y+4.5f);
        glVertex2f(x,        y+7.3f);
        glVertex2f(x+3.65f, y+4.5f);
    glEnd();

    // Roof (right half – darker shading)
    glColor3ub(132, 28, 28);
    glBegin(GL_TRIANGLES);
        glVertex2f(x+0.03f, y+7.3f);
        glVertex2f(x+3.65f, y+4.5f);
        glVertex2f(x-0.03f, y+7.3f);
    glEnd();

    // Eave strip
    glColor3ub(85, 16, 16);
    glBegin(GL_QUADS);
        glVertex2f(x-3.65f, y+4.35f); glVertex2f(x+3.65f, y+4.35f);
        glVertex2f(x+3.65f, y+4.55f); glVertex2f(x-3.65f, y+4.55f);
    glEnd();

    // Chimney body
    glColor3ub(112, 108, 110);
    glBegin(GL_QUADS);
        glVertex2f(x+1.55f, y+5.3f); glVertex2f(x+2.15f, y+5.3f);
        glVertex2f(x+2.15f, y+7.6f); glVertex2f(x+1.55f, y+7.6f);
    glEnd();

    // Chimney cap
    glColor3ub(78, 75, 76);
    glBegin(GL_QUADS);
        glVertex2f(x+1.45f, y+7.5f); glVertex2f(x+2.25f, y+7.5f);
        glVertex2f(x+2.25f, y+7.7f); glVertex2f(x+1.45f, y+7.7f);
    glEnd();

    // Door frame
    glColor3ub(108, 68, 18);
    glBegin(GL_QUADS);
        glVertex2f(x-0.9f, y);      glVertex2f(x+0.9f, y);
        glVertex2f(x+0.9f, y+2.6f); glVertex2f(x-0.9f, y+2.6f);
    glEnd();

    // Door arch (semicircle on top of frame)
    glColor3ub(108, 68, 18);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y+2.6f);
        for (int j = 0; j <= 12; j++) {
            float a = (float)j * 3.14159f / 12.0f;
            glVertex2f(x - 0.9f * cosf(a), y + 2.6f + 0.9f * sinf(a));
        }
    glEnd();

    // Door panel
    glColor3ub(82, 48, 10);
    glBegin(GL_QUADS);
        glVertex2f(x-0.75f, y+0.14f); glVertex2f(x+0.75f, y+0.14f);
        glVertex2f(x+0.75f, y+2.55f); glVertex2f(x-0.75f, y+2.55f);
    glEnd();

    // Door panel dividers
    glColor3ub(58, 33, 6);
    glLineWidth(1.2f);
    glBegin(GL_LINES);
        glVertex2f(x,       y+0.14f); glVertex2f(x,       y+2.55f);
        glVertex2f(x-0.75f, y+1.35f); glVertex2f(x+0.75f, y+1.35f);
    glEnd();

    // Door knob
    glColor3ub(218, 165, 32);
    glPushMatrix();
        glTranslatef(x+0.5f, y+0.82f, 0.0f);
        glutSolidSphere(0.12f, 12, 12);
    glPopMatrix();

    // ── Left window ──────────────────────────────────────────────────────────
    // Green shutters
    glColor3ub(52, 95, 52);
    glBegin(GL_QUADS);
        glVertex2f(x-3.08f, y+1.8f); glVertex2f(x-2.75f, y+1.8f);
        glVertex2f(x-2.75f, y+3.8f); glVertex2f(x-3.08f, y+3.8f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x-1.25f, y+1.8f); glVertex2f(x-0.92f, y+1.8f);
        glVertex2f(x-0.92f, y+3.8f); glVertex2f(x-1.25f, y+3.8f);
    glEnd();
    // Glass
    glColor3ub(130, 205, 250);
    glBegin(GL_QUADS);
        glVertex2f(x-2.75f, y+1.8f); glVertex2f(x-1.25f, y+1.8f);
        glVertex2f(x-1.25f, y+3.8f); glVertex2f(x-2.75f, y+3.8f);
    glEnd();
    // Window frame + cross
    glColor3ub(150, 102, 36);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x-2.75f, y+1.8f); glVertex2f(x-1.25f, y+1.8f);
        glVertex2f(x-1.25f, y+3.8f); glVertex2f(x-2.75f, y+3.8f);
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(x-2.0f,  y+1.8f); glVertex2f(x-2.0f,  y+3.8f);
        glVertex2f(x-2.75f, y+2.8f); glVertex2f(x-1.25f, y+2.8f);
    glEnd();

    // ── Right window ─────────────────────────────────────────────────────────
    glColor3ub(52, 95, 52);
    glBegin(GL_QUADS);
        glVertex2f(x+0.92f, y+1.8f); glVertex2f(x+1.25f, y+1.8f);
        glVertex2f(x+1.25f, y+3.8f); glVertex2f(x+0.92f, y+3.8f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x+2.75f, y+1.8f); glVertex2f(x+3.08f, y+1.8f);
        glVertex2f(x+3.08f, y+3.8f); glVertex2f(x+2.75f, y+3.8f);
    glEnd();
    glColor3ub(130, 205, 250);
    glBegin(GL_QUADS);
        glVertex2f(x+1.25f, y+1.8f); glVertex2f(x+2.75f, y+1.8f);
        glVertex2f(x+2.75f, y+3.8f); glVertex2f(x+1.25f, y+3.8f);
    glEnd();
    glColor3ub(150, 102, 36);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x+1.25f, y+1.8f); glVertex2f(x+2.75f, y+1.8f);
        glVertex2f(x+2.75f, y+3.8f); glVertex2f(x+1.25f, y+3.8f);
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(x+2.0f,  y+1.8f); glVertex2f(x+2.0f,  y+3.8f);
        glVertex2f(x+1.25f, y+2.8f); glVertex2f(x+2.75f, y+2.8f);
    glEnd();
}

// ── Pointed fence post ───────────────────────────────────────────────────────
void DrawFencePost(float x, float y)
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

// ── Spherical bush cluster ───────────────────────────────────────────────────
void DrawBush(float x, float y, float r,
              unsigned char R, unsigned char G, unsigned char B)
{
    glColor3ub(R, G, B);
    glPushMatrix(); glTranslatef(x-r*0.45f, y,        0.0f); glutSolidSphere(r*0.7f, 18, 18); glPopMatrix();
    glPushMatrix(); glTranslatef(x+r*0.45f, y,        0.0f); glutSolidSphere(r*0.7f, 18, 18); glPopMatrix();
    glPushMatrix(); glTranslatef(x,          y+r*0.3f, 0.0f); glutSolidSphere(r*0.8f, 18, 18); glPopMatrix();
}

// ── Animated smoke puffs from chimney ────────────────────────────────────────
void DrawSmoke(float cx, float baseY)
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

// ════════════════════════════════════════════════════════════════════════════════
//   MAIN DRAW
// ════════════════════════════════════════════════════════════════════════════════
void DrawAllComponents()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-12, 38, -19, 14);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ── Sky gradient (deep blue → pale sky blue) ──────────────────────────────
    glBegin(GL_QUADS);
        glColor3ub( 22,  82, 188); glVertex2f(-12, 14); glVertex2f(38, 14);
        glColor3ub(108, 182, 248); glVertex2f( 38,  3); glVertex2f(-12,  3);
    glEnd();

    // ── Far mountains (pale blue-grey) ────────────────────────────────────────
    glColor3ub(112, 148, 192);
    glBegin(GL_POLYGON);
        glVertex2f(-12, 3);   glVertex2f(-6, 10.5f);
        glVertex2f( 3,  5.0f); glVertex2f(12, 11.5f);
        glVertex2f(22,  4.5f); glVertex2f(29,  9.5f);
        glVertex2f(38,  5.5f); glVertex2f(38, 3);
    glEnd();

    // Snow caps
    glColor3ub(232, 242, 255);
    glBegin(GL_TRIANGLES);
        glVertex2f(-8, 9.0f);  glVertex2f(-6, 10.5f); glVertex2f(-4, 9.0f);
        glVertex2f(10, 10.1f); glVertex2f(12, 11.5f); glVertex2f(14, 10.1f);
        glVertex2f(27, 7.8f);  glVertex2f(29,  9.5f); glVertex2f(31, 7.8f);
    glEnd();

    // Near hills (darker green)
    glColor3ub(38, 112, 32);
    glBegin(GL_POLYGON);
        glVertex2f(-12, 3);   glVertex2f(-4, 6.5f);
        glVertex2f( 5,  3.5f); glVertex2f(15, 6.2f);
        glVertex2f(25,  3.2f); glVertex2f(38, 5.5f);
        glVertex2f(38, 3);    glVertex2f(-12, 3);
    glEnd();

    // ── Sun – glow rings + core + rotating rays ───────────────────────────────
    glColor3ub(255, 205, 52);
    glPushMatrix(); glTranslatef(31.5f, 11.5f, 0.0f); glutSolidSphere(1.9f, 48, 48); glPopMatrix();

    glColor3ub(255, 245, 128);
    glPushMatrix(); glTranslatef(31.5f, 11.5f, 0.0f); glutSolidSphere(1.3f, 48, 48); glPopMatrix();

    glColor3ub(255, 255, 185);
    glPushMatrix(); glTranslatef(31.5f, 11.5f, 0.0f); glutSolidSphere(0.88f, 48, 48); glPopMatrix();

    // Rays
    glColor3ub(255, 232, 75);
    glLineWidth(2.2f);
    for (int i = 0; i < 12; i++) {
        float a = rayAngle + i * (3.14159f * 2.0f / 12.0f);
        glBegin(GL_LINES);
            glVertex2f(31.5f + 2.1f * cosf(a), 11.5f + 2.1f * sinf(a));
            glVertex2f(31.5f + 3.5f * cosf(a), 11.5f + 3.5f * sinf(a));
        glEnd();
    }

    // ── Cloud 1 ───────────────────────────────────────────────────────────────
    glPushMatrix();
    glTranslatef(moveC, 0.0f, 0.0f);
    glColor3ub(255,255,255);
    glPushMatrix(); glTranslatef(1.0f,6.0f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(1.0f,7.0f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(2.0f,7.0f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(2.0f,6.0f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f,6.5f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(3.0f,6.5f,0); glutSolidSphere(0.7f,30,30); glPopMatrix();
    glPopMatrix();

    // ── Cloud 2 ───────────────────────────────────────────────────────────────
    glPushMatrix();
    glTranslatef(moveC, 0.0f, 0.0f);
    glColor3ub(255,255,255);
    glPushMatrix(); glTranslatef(15.0f,9.0f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(15.0f,8.0f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(16.0f,8.0f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(16.0f,9.0f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(14.0f,8.5f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(17.0f,8.5f,0); glutSolidSphere(0.8f,30,30); glPopMatrix();
    glPopMatrix();

    // ── Cloud 3 ───────────────────────────────────────────────────────────────
    glPushMatrix();
    glTranslatef(moveC, 0.0f, 0.0f);
    glColor3ub(255,255,255);
    glPushMatrix(); glTranslatef(22.0f,8.0f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(22.0f,7.0f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(23.0f,8.0f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(23.0f,7.0f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(24.0f,7.5f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPushMatrix(); glTranslatef(21.0f,7.5f,0); glutSolidSphere(0.75f,30,30); glPopMatrix();
    glPopMatrix();

    // ── Sea ───────────────────────────────────────────────────────────────────
    glBegin(GL_POLYGON);
        glColor3ub(52, 92, 215);
        glVertex2f( 38,-19); glVertex2f( 38,-11);
        glVertex2f(-12,-11); glVertex2f(-12,-19);
    glEnd();

    // Animated wave ripples
    glColor3ub(82, 128, 232);
    glLineWidth(1.1f);
    for (int i = 0; i < 6; i++) {
        float wy = -11.8f - i * 1.2f;
        glBegin(GL_LINE_STRIP);
            for (float wx = -12.0f; wx <= 38.0f; wx += 0.35f)
                glVertex2f(wx, wy + 0.22f * sinf(wx * 1.3f + moveB1 * 2.5f));
        glEnd();
    }

    // ── Ground ────────────────────────────────────────────────────────────────
    glBegin(GL_POLYGON);
        glColor3ub(30, 130, 12);
        glVertex2f(90.0f,-12.5f); glVertex2f(38.0f,-12.0f);
        glVertex2f(38.0f,  3.0f); glVertex2f(-12.0f, 3.0f);
        glVertex2f(-12.0f,-11.0f);
    glEnd();

    // Lighter grass strip at top
    glBegin(GL_QUADS);
        glColor3ub(48, 160, 28);
        glVertex2f(-12, 2.1f); glVertex2f(38, 2.6f);
        glVertex2f( 38, 3.0f); glVertex2f(-12, 3.0f);
    glEnd();

    // ── Dirt path to house 1 ─────────────────────────────────────────────────
    glColor3ub(162, 132, 72);
    glBegin(GL_QUADS);
        glVertex2f(-2.6f, -0.2f); glVertex2f( 0.6f, -0.2f);
        glVertex2f( 0.6f, -7.0f); glVertex2f(-2.6f, -7.0f);
    glEnd();

    // ── Bushes ────────────────────────────────────────────────────────────────
    DrawBush( 6.5f, -2.5f, 0.55f, 28, 118, 20);
    DrawBush( 7.6f, -2.0f, 0.42f, 35, 130, 25);
    DrawBush(-9.5f, -2.5f, 0.52f, 25, 112, 18);
    DrawBush(35.5f, -3.0f, 0.50f, 30, 120, 22);
    DrawBush(36.5f, -2.5f, 0.38f, 25, 115, 18);

    // ── Flowers (stem + sphere bloom) ─────────────────────────────────────────
    {
        float fX[5]  = {  5.0f,  8.2f, -8.0f, -10.5f,  4.0f };
        float fY[5]  = { -2.8f, -1.5f, -3.0f,  -2.0f, -1.8f };
        unsigned char fR[5] = {255, 255, 200, 255, 255};
        unsigned char fG[5] = { 80, 218,  80,  80, 148};
        unsigned char fB[5] = {120,  50, 255, 120, 255};

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

    // ── Houses ────────────────────────────────────────────────────────────────
    DrawHouse(-2.0f, -7.2f);    // House 1 (left)
    DrawHouse(11.0f, -9.2f);    // House 2 (right)

    // Chimney smoke
    DrawSmoke(-2.0f + 1.85f, -7.2f + 7.7f);   // House 1 chimney top ≈ (−0.15, 0.5)
    DrawSmoke(11.0f + 1.85f, -9.2f + 7.7f);   // House 2 chimney top ≈ (12.85, −1.5)

    // ── Pine trees ────────────────────────────────────────────────────────────
    DrawPineTree(19.0f, -10.0f, 1.00f);
    DrawPineTree(23.5f, -10.0f, 0.88f);
    DrawPineTree(29.5f, -10.0f, 1.12f);
    DrawPineTree(33.8f, -10.5f, 0.72f);

    // ── Fence (with gate opening at path) ────────────────────────────────────
    for (float fx = -11.5f; fx <= 36.5f; fx += 2.2f) {
        if (fx > -2.8f && fx < 0.8f) continue;   // gate gap for dirt path
        DrawFencePost(fx, -0.8f);
    }
    // Fence rails
    glColor3ub(198, 165, 112);
    glLineWidth(1.4f);
    // Left section of rail (before gate)
    glBegin(GL_LINES);
        glVertex2f(-11.5f, -0.15f); glVertex2f(-2.8f, -0.15f);
        glVertex2f(-11.5f, -0.45f); glVertex2f(-2.8f, -0.45f);
    glEnd();
    // Right section of rail (after gate)
    glBegin(GL_LINES);
        glVertex2f(0.8f, -0.15f); glVertex2f(36.5f, -0.15f);
        glVertex2f(0.8f, -0.45f); glVertex2f(36.5f, -0.45f);
    glEnd();

    // ── Railway ───────────────────────────────────────────────────────────────
    // Upper rail
    glColor3ub(155, 29, 29);
    glBegin(GL_QUADS);
        glVertex2f(-12,    2.00f); glVertex2f(38,    3.00f);
        glVertex2f(37.98f, 2.69f); glVertex2f(-11.98f,1.71f);
    glEnd();
    // Lower rail
    glBegin(GL_QUADS);
        glVertex2f(-12.07f, 0.72f); glVertex2f(-12.07f, 0.48f);
        glVertex2f( 38.02f, 1.52f); glVertex2f( 38.0f,  1.70f);
    glEnd();
    // Sleepers
    glColor3ub(0,0,0);
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

    // ── Flying birds (V-shaped flock) ─────────────────────────────────────────
    glColor3ub(18, 18, 18);
    glLineWidth(1.8f);
    {
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

    // ── Boat 1  (left → right, with sails) ───────────────────────────────────
    glPushMatrix();
    glTranslatef(moveB1, 0.0f, 0.0f);

    // Hull
    glColor3ub(139, 69, 19);
    glBegin(GL_QUADS);
        glVertex2f( 1.0f,-14.0f); glVertex2f( 1.5f,-13.0f);
        glVertex2f(-2.0f,-13.0f); glVertex2f(-3.0f,-14.0f);
    glEnd();
    // Base
    glColor3ub(0,0,0);
    glBegin(GL_QUADS);
        glVertex2f( 2.0f,-14.5f); glVertex2f( 2.0f,-14.0f);
        glVertex2f(-3.0f,-14.0f); glVertex2f(-3.0f,-14.5f);
    glEnd();
    // Bow / stern tapers
    glBegin(GL_TRIANGLES);
        glVertex2f(-3.0f,-14.5f); glVertex2f(-3.0f,-14.0f); glVertex2f(-4.5f,-13.7f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f( 2.0f,-14.5f); glVertex2f( 3.5f,-13.7f); glVertex2f( 2.0f,-14.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f( 2.0f,-14.0f); glVertex2f( 1.5f,-13.0f); glVertex2f( 1.0f,-14.0f);
    glEnd();
    // Mast
    glColor3ub(101, 67, 33);
    glLineWidth(2.2f);
    glBegin(GL_LINES);
        glVertex2f(-0.5f,-13.0f); glVertex2f(-0.5f,-10.2f);
    glEnd();
    // Main sail (forward)
    glColor3ub(242, 230, 205);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f,-10.2f); glVertex2f(2.4f,-12.7f); glVertex2f(-0.5f,-13.0f);
    glEnd();
    // Back sail
    glColor3ub(212, 200, 178);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f,-10.2f); glVertex2f(-0.5f,-13.0f); glVertex2f(-3.0f,-12.7f);
    glEnd();

    glPopMatrix();

    // ── Boat 2  (right → left, cabin cruiser) ────────────────────────────────
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
    glBegin(GL_TRIANGLES);
        glColor3ub(0,0,0);
        glVertex2f(17.0f,-18.0f); glVertex2f(17.0f,-17.5f); glVertex2f(15.5f,-17.2f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3ub(0,0,0);
        glVertex2f(22.0f,-17.5f); glVertex2f(22.0f,-18.0f); glVertex2f(23.5f,-17.2f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3ub(0,0,0);
        glVertex2f(17.0f,-17.5f); glVertex2f(18.0f,-17.5f); glVertex2f(17.5f,-16.5f);
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

// ── Timer callbacks ───────────────────────────────────────────────────────────
void updateC(int v)
{
    moveC = (moveC > 36.0f) ? -38.0f : moveC + 0.15f;
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
    moveB2 -= 0.13f;
    glutTimerFunc(20, updateB2, 0);
    glutPostRedisplay();
}

void updateExtras(int v)
{
    moveBird  += 0.08f;
    if (moveBird > 52.0f) moveBird = -26.0f;

    smokeOff = fmodf(smokeOff + 0.007f, 1.0f);
    rayAngle += 0.004f;

    glutTimerFunc(30, updateExtras, 0);
    glutPostRedisplay();
}

// ── Input handlers ────────────────────────────────────────────────────────────
void handleKeypress(unsigned char key, int x, int y)
{
    if      (key == 's') speed = 0.0f;
    else if (key == 'r') speed = 0.02f;
    glutPostRedisplay();
}

void handleMouse(int button, int state, int x, int y)
{
    if      (button == GLUT_LEFT_BUTTON)  speed += 0.05f;
    else if (button == GLUT_RIGHT_BUTTON) speed -= 0.05f;
    glutPostRedisplay();
}

// ── Boilerplate ───────────────────────────────────────────────────────────────
void display(void) { DrawAllComponents(); }
void init()        { glClearColor(0.42f, 0.71f, 0.98f, 1.0f); }

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1300, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(" Village Scenery – Enhanced ");
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
