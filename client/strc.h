#ifndef STRC_H
#define STRC_H
#include <QSqlQuery>
#include <QVector>
#endif // STRC_H

struct T{
    //QVector<int> data_n[6];
    int flag;
};

struct t_m{
    int gol;
};

struct t_c{
    int gol;
};

struct t_info{
    int kind[4];
};

struct t_baru{
    unsigned char nama[400];
};

int proses_q( QSqlQuery *q, const char *s, ...);

#define ID_KIND_COMPANY             100
#define ID_KIND_DEPARTMENT          200
#define ID_KIND_LOCATION            300
#define ID_KIND_GROUP               400

#define ID_OFF_RUTE_ASET            500
#define ID_KIND_RECIP_ENGINE        600
#define ID_KIND_RECIP_COMPRESSOR    700
#define ID_KIND_ROTATING_MACHINE    800
#define ID_KIND_ROTATING_EQUIP_V    810 //untuk alat Viro
#define ID_KIND_STRUCTURE           900
#define ID_KIND_PIPE                1000
#define ID_KIND_TANK                1100

/* LEVEL POINT */
#define ID_KIND_ENGINE_CYL          5100
#define ID_KIND_COMP_THROW          5200
#define ID_KIND_COMP_VALVE          5300
#define ID_KIND_ROTATING_POINT      5400
#define ID_KIND_STRUCTURE_POINT     5500
#define ID_KIND_PIPE_POINT          5600

/* jika belum ada diatas */
#define ID_KIND_EQUIPMENT_OTHER     10100
#define ID_KIND_COMPONENT_OTHER     10200

#define ID_KIND_OTHER               20100
#define ID_KIND_PARAM               30100  /* unutk menunjukkan bahwa ini adalah parameter */

#define ICON_COMPANY            ":/images/factory.png"
#define ICON_DEPT               ":/images/dept.png"
#define ICON_LOCATION           ":/images/location.png"
#define ICON_GROUP              ":/images/star.png"

#define ICON_OFF_ROUTE_ASET     ":/images/offroute.png"
#define ICON_RECIP_ENGINE       ":/images/piston2.png"
#define ICON_RECIP_COMPRESSOR   ":/images/compressor.png"
#define ICON_ROTATING_MACHINE   ":/images/gear.png"
#define ICON_STRUCTURE          ":/images/Home.png"
#define ICON_PIPE               ":/images/curve_3.png"
#define ICON_TANK               ":/images/container.png"

#define ICON_ENGINE_CYL         ":/images/piston3.png"
#define ICON_COMP_THROW         ":/images/ring.png"
#define ICON_COMP_VALVE         ":/images/conrod.png"
#define ICON_ROTATING_POINT     ":/images/tag.png"
#define ICON_STRUCTURE_POINT    ":/images/puzzle.png"
#define ICON_PIPE_POINT         ":/images/new.png"

/* icon untuk setup data rotating */
#define ICON_SETUP_BUT          ":/images/icon_setting.png"

#define ICON_EQUIPMENT_OTHER    ":/images/robot.png"
#define ICON_COMPONENT_OTHER    ":/images/service.png"

#define ICON_OTHER              ":/images/leaf.png"

#define ICON_NEW_ASET           ":/images/new_aset.png"
#define ICON_WIZZARD_ASET       ":/images/wizzard_aset.png"
#define ICON_WIZZARD_ENGINE     ":/images/wizzard_engine.png"
#define ICON_WIZZARD_COMPRESSOR ":/images/wizzard_compressor.png"
#define ICON_WIZZARD_ROTATING   ":/images/wizzard_rotating.png"
#define ICON_NEW_PARAMETER      ":/images/new_parameter.png"
#define ICON_NEW_ROUTE          ":/images/new_route.png"
#define ICON_COPY_ASET          ":/images/copy.png"
#define ICON_PASTE_ASET         ":/images/paste.png"
#define ICON_DELETE_ASET        ":/images/delete_aset.png"
#define ICON_VIEW_ASET_RUTE     ":/images/rute2.png"

#define ICON_REFRESH_TREE       ":/images/refresh.png"
#define ICON_VIRO_WIZARD_ASET       ":/images/blades.png"
#define ICON_VIRO_ASET_ROTATE_MOTOR       ":/images/motor.png"
#define ICON_VIRO_ASET_ROTATE_PUMP       ":/images/pump.png"

#define MOTOR_DC    ":/images/electric-motor.png"

#define ROLE_TREE_ASET_ID           0x110
#define ROLE_TREE_ASET_KIND         0x120
#define ROLE_TREE_ASET_ID_TIPE_PARAM    0x130
#define ROLE_TREE_ASET_ID_PARAM     0x140
