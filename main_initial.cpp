#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <windows.h>

// ══════════════════════════════════════════════════════════════════════════════
//  REUSABLE PRIMITIVE HELPERS
// ══════════════════════════════════════════════════════════════════════════════

// ── Professional 4-tier pine tree with bark texture and tip spire ─────────────
void DrawPineTree(float cx, float cy, float sc)
{
    // -- Trunk (dark bark + highlight strip + bark lines) ----------------------
    glColor3ub(62, 38, 15);
    glBegin(GL_QUADS);
        glVertex2f(cx - 0.28f*sc, cy);
        glVertex2f(cx + 0.28f*sc, cy);
        glVertex2f(cx + 0.28f*sc, cy + 2.0f*sc);
        glVertex2f(cx - 0.28f*sc, cy + 2.0f*sc);
    glEnd();
    // Trunk highlight strip
    glColor3ub(105, 68, 28);
    glBegin(GL_QUADS);
        glVertex2f(cx - 0.07f*sc, cy);
        glVertex2f(cx + 0.07f*sc, cy);
        glVertex2f(cx + 0.05f*sc, cy + 2.0f*sc);
        glVertex2f(cx - 0.05f*sc, cy + 2.0f*sc);
    glEnd();
    // Bark texture lines
    glColor3ub(42, 25, 8);
    glLineWidth(0.7f);
    glBegin(GL_LINES);
        glVertex2f(cx - 0.28f*sc, cy + 0.50f*sc);  glVertex2f(cx + 0.28f*sc, cy + 0.60f*sc);
        glVertex2f(cx - 0.28f*sc, cy + 1.10f*sc);  glVertex2f(cx + 0.28f*sc, cy + 1.20f*sc);
        glVertex2f(cx - 0.28f*sc, cy + 1.65f*sc);  glVertex2f(cx + 0.28f*sc, cy + 1.72f*sc);
    glEnd();

    // -- Tier 1 (bottom, darkest shadow foliage) --------------------------------
    glColor3ub(14, 72, 22);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 2.2f*sc,  cy + 0.9f*sc);
        glVertex2f(cx,             cy + 3.8f*sc);
        glVertex2f(cx + 2.2f*sc,  cy + 0.9f*sc);
    glEnd();
    // Tier 1 left-face highlight
    glColor3ub(24, 102, 36);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 1.8f*sc,  cy + 1.3f*sc);
        glVertex2f(cx - 0.10f*sc, cy + 3.8f*sc);
        glVertex2f(cx - 0.10f*sc, cy + 1.3f*sc);
    glEnd();

    // -- Tier 2 (middle) --------------------------------------------------------
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

    // -- Tier 3 (upper-mid) -----------------------------------------------------
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

    // -- Tier 4 (top, brightest) ------------------------------------------------
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

    // -- Tip spire --------------------------------------------------------------
    glColor3ub(82, 195, 105);
    glBegin(GL_TRIANGLES);
        glVertex2f(cx - 0.26f*sc, cy + 6.5f*sc);
        glVertex2f(cx,             cy + 7.5f*sc);
        glVertex2f(cx + 0.26f*sc, cy + 6.5f*sc);
    glEnd();
}

// ── Village house (thatched roof, mud/clay walls, bamboo details, porch) ──────
void DrawHouse(float x, float y)
{
    // Foundation slab
    glColor3ub(108, 80, 50);
    glBegin(GL_QUADS);
        glVertex2f(x-3.4f, y-0.38f); glVertex2f(x+3.4f, y-0.38f);
        glVertex2f(x+3.4f, y+0.12f); glVertex2f(x-3.4f, y+0.12f);
    glEnd();

    // Main mud/clay wall
    glColor3ub(195, 152, 100);
    glBegin(GL_QUADS);
        glVertex2f(x-3.0f, y);      glVertex2f(x+3.0f, y);
        glVertex2f(x+3.0f, y+4.5f); glVertex2f(x-3.0f, y+4.5f);
    glEnd();
    // Right wall shadow strip
    glColor3ub(162, 122, 78);
    glBegin(GL_QUADS);
        glVertex2f(x+2.62f, y);      glVertex2f(x+3.0f, y);
        glVertex2f(x+3.0f,  y+4.5f); glVertex2f(x+2.62f, y+4.5f);
    glEnd();

    // Bamboo/wood corner posts
    glColor3ub(112, 72, 28);
    glBegin(GL_QUADS);
        glVertex2f(x-3.0f,  y);      glVertex2f(x-2.68f, y);
        glVertex2f(x-2.68f, y+4.5f); glVertex2f(x-3.0f,  y+4.5f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x+2.68f, y);      glVertex2f(x+3.0f, y);
        glVertex2f(x+3.0f,  y+4.5f); glVertex2f(x+2.68f, y+4.5f);
    glEnd();

    // Horizontal wall texture strips (bamboo weave)
    glColor3ub(148, 112, 68);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        glVertex2f(x-3.0f, y+1.5f); glVertex2f(x+3.0f, y+1.5f);
        glVertex2f(x-3.0f, y+3.0f); glVertex2f(x+3.0f, y+3.0f);
    glEnd();

    // ── Thatched roof (layered straw strips, bottom to peak) ──────────────────
    // Layer 1 – base, widest, darkest
    glColor3ub(142, 98, 22);
    glBegin(GL_QUADS);
        glVertex2f(x-3.85f, y+4.15f); glVertex2f(x+3.85f, y+4.15f);
        glVertex2f(x+3.15f, y+5.15f); glVertex2f(x-3.15f, y+5.15f);
    glEnd();
    // Layer 2
    glColor3ub(158, 112, 32);
    glBegin(GL_QUADS);
        glVertex2f(x-3.15f, y+4.95f); glVertex2f(x+3.15f, y+4.95f);
        glVertex2f(x+2.40f, y+5.90f); glVertex2f(x-2.40f, y+5.90f);
    glEnd();
    // Layer 3
    glColor3ub(172, 128, 45);
    glBegin(GL_QUADS);
        glVertex2f(x-2.4f, y+5.70f); glVertex2f(x+2.4f, y+5.70f);
        glVertex2f(x+1.6f, y+6.60f); glVertex2f(x-1.6f, y+6.60f);
    glEnd();
    // Layer 4
    glColor3ub(185, 145, 58);
    glBegin(GL_QUADS);
        glVertex2f(x-1.6f,  y+6.40f); glVertex2f(x+1.6f,  y+6.40f);
        glVertex2f(x+0.75f, y+7.10f); glVertex2f(x-0.75f, y+7.10f);
    glEnd();
    // Peak triangle
    glColor3ub(198, 160, 70);
    glBegin(GL_TRIANGLES);
        glVertex2f(x-0.75f, y+6.95f);
        glVertex2f(x,        y+7.65f);
        glVertex2f(x+0.75f, y+6.95f);
    glEnd();

    // Eave shadow line at bottom of roof
    glColor3ub(90, 60, 12);
    glBegin(GL_QUADS);
        glVertex2f(x-3.90f, y+4.10f); glVertex2f(x+3.90f, y+4.10f);
        glVertex2f(x+3.90f, y+4.32f); glVertex2f(x-3.90f, y+4.32f);
    glEnd();

    // Thatch straw texture lines (diagonal streaks)
    glColor3ub(110, 75, 15);
    glLineWidth(0.7f);
    for (int i = 0; i < 7; i++) {
        float lx = x - 3.4f + i * 1.05f;
        glBegin(GL_LINES);
            glVertex2f(lx,         y+4.15f);
            glVertex2f(lx + 0.32f, y+7.10f);
        glEnd();
    }

    // ── Chimney (brick pattern with mortar lines) ──────────────────────────────
    glColor3ub(138, 82, 52);
    glBegin(GL_QUADS);
        glVertex2f(x+1.45f, y+5.40f); glVertex2f(x+2.05f, y+5.40f);
        glVertex2f(x+2.05f, y+7.62f); glVertex2f(x+1.45f, y+7.62f);
    glEnd();
    // Brick mortar lines
    glColor3ub(108, 58, 30);
    glLineWidth(0.7f);
    glBegin(GL_LINES);
        glVertex2f(x+1.45f, y+5.95f); glVertex2f(x+2.05f, y+5.95f);
        glVertex2f(x+1.45f, y+6.50f); glVertex2f(x+2.05f, y+6.50f);
        glVertex2f(x+1.45f, y+7.05f); glVertex2f(x+2.05f, y+7.05f);
        glVertex2f(x+1.75f, y+5.40f); glVertex2f(x+1.75f, y+7.62f);
    glEnd();
    // Chimney cap
    glColor3ub(82, 50, 22);
    glBegin(GL_QUADS);
        glVertex2f(x+1.32f, y+7.52f); glVertex2f(x+2.18f, y+7.52f);
        glVertex2f(x+2.18f, y+7.75f); glVertex2f(x+1.32f, y+7.75f);
    glEnd();

    // ── Village bamboo plank door ──────────────────────────────────────────────
    // Door surround/frame
    glColor3ub(82, 50, 16);
    glBegin(GL_QUADS);
        glVertex2f(x-1.05f, y);      glVertex2f(x+1.05f, y);
        glVertex2f(x+1.05f, y+2.90f); glVertex2f(x-1.05f, y+2.90f);
    glEnd();
    // Top lintel bar
    glBegin(GL_QUADS);
        glVertex2f(x-1.05f, y+2.72f); glVertex2f(x+1.05f, y+2.72f);
        glVertex2f(x+1.05f, y+3.02f); glVertex2f(x-1.05f, y+3.02f);
    glEnd();
    // Three vertical plank panels
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
    // Plank divider + horizontal cross-bar lines
    glColor3ub(62, 38, 10);
    glLineWidth(0.8f);
    glBegin(GL_LINES);
        glVertex2f(x-0.38f, y+0.12f); glVertex2f(x-0.38f, y+2.68f);
        glVertex2f(x+0.24f, y+0.12f); glVertex2f(x+0.24f, y+2.68f);
        glVertex2f(x-1.05f, y+1.42f); glVertex2f(x+1.05f, y+1.42f);
    glEnd();
    // Door knob
    glColor3ub(195, 148, 18);
    glPushMatrix();
        glTranslatef(x+0.62f, y+0.88f, 0.0f);
        glutSolidSphere(0.09f, 12, 12);
    glPopMatrix();

    // ── Left window (bamboo frame + light blue glass + cross divider) ──────────
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
        glVertex2f(x-2.00f,  y+2.06f); glVertex2f(x-2.00f,  y+3.58f);
        glVertex2f(x-2.72f,  y+2.82f); glVertex2f(x-1.28f,  y+2.82f);
    glEnd();

    // ── Right window ───────────────────────────────────────────────────────────
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
        glVertex2f(x+2.00f,  y+2.06f); glVertex2f(x+2.00f,  y+3.58f);
        glVertex2f(x+1.28f,  y+2.82f); glVertex2f(x+2.72f,  y+2.82f);
    glEnd();

    // ── Front porch step ───────────────────────────────────────────────────────
    glColor3ub(128, 96, 58);
    glBegin(GL_QUADS);
        glVertex2f(x-1.5f, y-0.38f); glVertex2f(x+1.5f, y-0.38f);
        glVertex2f(x+1.5f, y+0.05f); glVertex2f(x-1.5f, y+0.05f);
    glEnd();
}

// ── Spherical bush cluster ────────────────────────────────────────────────────
void DrawBush(float x, float y, float r,
              unsigned char R, unsigned char G, unsigned char B)
{
    glColor3ub(R, G, B);
    glPushMatrix(); glTranslatef(x-r*0.45f, y,         0.0f); glutSolidSphere(r*0.7f, 18, 18); glPopMatrix();
    glPushMatrix(); glTranslatef(x+r*0.45f, y,         0.0f); glutSolidSphere(r*0.7f, 18, 18); glPopMatrix();
    glPushMatrix(); glTranslatef(x,          y+r*0.3f, 0.0f); glutSolidSphere(r*0.8f, 18, 18); glPopMatrix();
}


// ══════════════════════════════════════════════════════════════════════════════
//  SCENE SECTION FUNCTIONS
// ══════════════════════════════════════════════════════════════════════════════

// 1. Sky gradient (deep blue at top → pale blue at horizon)
void DrawSky()
{
    glBegin(GL_QUADS);
        glColor3ub( 22,  82, 188); glVertex2f(-12, 14); glVertex2f(38, 14);
        glColor3ub(108, 182, 248); glVertex2f( 38,  3); glVertex2f(-12,  3);
    glEnd();
}

// 2. Static sun – three glow rings + core (no rotating rays)
void DrawSun()
{
    glColor3ub(255, 205, 52);
    glPushMatrix(); glTranslatef(31.5f, 11.5f, 0.0f); glutSolidSphere(1.9f, 48, 48); glPopMatrix();
    glColor3ub(255, 245, 128);
    glPushMatrix(); glTranslatef(31.5f, 11.5f, 0.0f); glutSolidSphere(1.3f, 48, 48); glPopMatrix();
    glColor3ub(255, 255, 185);
    glPushMatrix(); glTranslatef(31.5f, 11.5f, 0.0f); glutSolidSphere(0.88f, 48, 48); glPopMatrix();
    // Static rays at fixed angles
    glColor3ub(255, 232, 75);
    glLineWidth(2.2f);
    for (int i = 0; i < 12; i++) {
        float a = i * (3.14159f * 2.0f / 12.0f);
        glBegin(GL_LINES);
            glVertex2f(31.5f + 2.1f * cosf(a), 11.5f + 2.1f * sinf(a));
            glVertex2f(31.5f + 3.5f * cosf(a), 11.5f + 3.5f * sinf(a));
        glEnd();
    }
}

// 3. Far mountains with snow caps + peak highlights
void DrawMountains()
{
    // Mountain body
    glColor3ub(112, 148, 192);
    glBegin(GL_POLYGON);
        glVertex2f(-12, 3);    glVertex2f(-6, 10.5f);
        glVertex2f(  3, 5.0f); glVertex2f(12, 11.5f);
        glVertex2f( 22, 4.5f); glVertex2f(29,  9.5f);
        glVertex2f( 38, 5.5f); glVertex2f(38,  3);
    glEnd();
    // Snow caps
    glColor3ub(232, 242, 255);
    glBegin(GL_TRIANGLES);
        glVertex2f( -8, 9.0f);  glVertex2f(-6, 10.5f); glVertex2f(-4, 9.0f);
        glVertex2f( 10,10.1f);  glVertex2f(12, 11.5f); glVertex2f(14,10.1f);
        glVertex2f( 27, 7.8f);  glVertex2f(29,  9.5f); glVertex2f(31, 7.8f);
    glEnd();
    // Peak highlight sparkle
    glColor3ub(255, 255, 255);
    glBegin(GL_TRIANGLES);
        glVertex2f(-6.35f,10.1f); glVertex2f(-6.0f,10.5f); glVertex2f(-5.65f,10.1f);
        glVertex2f(11.65f,11.0f); glVertex2f(12.0f,11.5f); glVertex2f(12.35f,11.0f);
        glVertex2f(28.68f, 9.0f); glVertex2f(29.0f, 9.5f); glVertex2f(29.32f, 9.0f);
    glEnd();
}

// 4. Near hills – three layered polygons with grass texture patches on crests
void DrawHills()
{
    // Back hill layer (slightly muted green)
    glColor3ub(52, 118, 44);
    glBegin(GL_POLYGON);
        glVertex2f(-12, 3);    glVertex2f(-5, 7.0f);
        glVertex2f(  2, 4.0f); glVertex2f(10, 7.2f);
        glVertex2f( 18, 3.9f); glVertex2f(26, 6.6f);
        glVertex2f( 38, 4.6f); glVertex2f(38, 3); glVertex2f(-12, 3);
    glEnd();
    // Mid hill layer (richer green)
    glColor3ub(38, 112, 32);
    glBegin(GL_POLYGON);
        glVertex2f(-12, 3);    glVertex2f(-4, 6.5f);
        glVertex2f(  5, 3.5f); glVertex2f(15, 6.2f);
        glVertex2f( 25, 3.2f); glVertex2f(38, 5.5f);
        glVertex2f( 38, 3);    glVertex2f(-12, 3);
    glEnd();
    // Hill crest highlight edge
    glColor3ub(62, 145, 40);
    glBegin(GL_POLYGON);
        glVertex2f(-12, 2.85f); glVertex2f(-4, 6.35f);
        glVertex2f(  5, 3.35f); glVertex2f(15, 6.05f);
        glVertex2f( 25, 3.05f); glVertex2f(38, 5.35f);
        glVertex2f( 38, 3.0f);  glVertex2f(-12, 3.0f);
    glEnd();
    // Dark grass tufts / texture patches on hill crests
    glColor3ub(25, 85, 20);
    glBegin(GL_TRIANGLES);
        glVertex2f(-4.6f, 6.2f); glVertex2f(-4.0f, 6.5f); glVertex2f(-3.4f, 6.2f);
        glVertex2f(14.4f, 5.9f); glVertex2f(15.0f, 6.2f); glVertex2f(15.6f, 5.9f);
        glVertex2f(25.6f, 5.0f); glVertex2f(26.2f, 5.5f); glVertex2f(26.8f, 5.0f);
    glEnd();
}

// 5. River – static water body only (no animated waves)
void DrawRiver()
{
    // Water body (gradient: darker at bottom, lighter near surface)
    glBegin(GL_QUADS);
        glColor3ub(35,  72, 185); glVertex2f(-12,-19); glVertex2f(38,-19);
        glColor3ub(55, 102, 218); glVertex2f(38, -11); glVertex2f(-12,-11);
    glEnd();
    // Near-shore lighter water tint
    glColor3ub(75, 128, 232);
    glBegin(GL_QUADS);
        glVertex2f(-12,-11.55f); glVertex2f(38,-11.55f);
        glVertex2f(38, -11.0f);  glVertex2f(-12,-11.0f);
    glEnd();
}

// 6. Ground – plain green ground (no bank border strips, no reeds, no path)
void DrawGround()
{
    // Main green ground polygon
    glBegin(GL_POLYGON);
        glColor3ub(30, 130, 12);
        glVertex2f(90.0f,-12.5f); glVertex2f(38.0f,-12.0f);
        glVertex2f(38.0f,  3.0f); glVertex2f(-12.0f, 3.0f);
        glVertex2f(-12.0f,-11.0f);
    glEnd();
    // Lighter grass crest strip at top (hill meeting line)
    glBegin(GL_QUADS);
        glColor3ub(48, 160, 28);
        glVertex2f(-12, 2.1f); glVertex2f(38, 2.6f);
        glVertex2f( 38, 3.0f); glVertex2f(-12, 3.0f);
    glEnd();
}

// 7. Scattered bush clusters
void DrawBushes()
{
    DrawBush( 6.5f, -2.5f, 0.55f, 28, 118, 20);
    DrawBush( 7.6f, -2.0f, 0.42f, 35, 130, 25);
    DrawBush(-9.5f, -2.5f, 0.52f, 25, 112, 18);
    DrawBush(35.5f, -3.0f, 0.50f, 30, 120, 22);
    DrawBush(36.5f, -2.5f, 0.38f, 25, 115, 18);
}

// 8. Both village houses (no chimney smoke)
void DrawAllHouses()
{
    DrawHouse(-2.0f, -7.2f);   // House 1 (left)
    DrawHouse(11.0f, -9.2f);   // House 2 (right)
}

// 9. Four pine trees along the right bank
void DrawAllTrees()
{
    DrawPineTree(19.0f, -10.0f, 1.00f);
    DrawPineTree(23.5f, -10.0f, 0.88f);
    DrawPineTree(29.5f, -10.0f, 1.12f);
    DrawPineTree(33.8f, -10.5f, 0.72f);
}

// 10. Railway tracks + sleepers (perspective-foreshortened)
void DrawRailway()
{
    // Upper rail
    glColor3ub(155, 29, 29);
    glBegin(GL_QUADS);
        glVertex2f(-12,     2.00f); glVertex2f(38,     3.00f);
        glVertex2f(37.98f,  2.69f); glVertex2f(-11.98f,1.71f);
    glEnd();
    // Lower rail
    glBegin(GL_QUADS);
        glVertex2f(-12.07f, 0.72f); glVertex2f(-12.07f, 0.48f);
        glVertex2f( 38.02f, 1.52f); glVertex2f( 38.0f,  1.70f);
    glEnd();
    // Sleepers
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

// 11. Two static boats on the river (no translation / movement)
void DrawBoats()
{
    // ── Boat 1 (sailboat) ────────────────────────────────────────────────────
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

    // ── Boat 2 (cabin cruiser) ────────────────────────────────────────────────
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
}


// ══════════════════════════════════════════════════════════════════════════════
//  MASTER DRAW – calls every scene component in back-to-front painter order
// ══════════════════════════════════════════════════════════════════════════════
void DrawAllComponents()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-12, 38, -19, 14);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    DrawSky();        //  1. Sky gradient
    DrawSun();        //  2. Static sun + fixed rays
    DrawMountains();  //  3. Far mountains + snow caps
    DrawHills();      //  4. Layered near hills with crest detail
    DrawRiver();      //  5. Static river water body
    DrawGround();     //  6. Ground (no bank borders)
    DrawBushes();     //  7. Bush clusters
    DrawAllHouses();  //  8. Village houses (no smoke)
    DrawAllTrees();   //  9. Pine trees
    DrawRailway();    // 10. Railway tracks + sleepers
    DrawBoats();      // 11. Static boats on river

    glutSwapBuffers();
}

// ── Display callback ──────────────────────────────────────────────────────────
void display(void) { DrawAllComponents(); }
void init()        { glClearColor(0.42f, 0.71f, 0.98f, 1.0f); }

// ── Entry point ───────────────────────────────────────────────────────────────
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1300, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(" Village Scenery – Initial ");
    init();

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
