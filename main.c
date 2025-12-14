#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>
#include <libplayerc/playerc.h>

int main(int argc, const char **argv) {
    playerc_client_t *client;
    playerc_position2d_t *position2d;

    /* Objective */
    double gx = -11.4;
    double gy = 0.0;
    double ga = -90;

    // tolerances (vfh has distance_epsilon so it may be useless)
    const double pos_tol = 0.05;
    const double ang_tol = 0.05;
	
    int state = 0;

    /* Connect to the client, asumming it is on port 6665 */
    client = playerc_client_create(NULL, "localhost", 6665);
    if (playerc_client_connect(client) != 0) {
        fprintf(stderr, "Error connecting: %s\n", playerc_error_str());
        return -1;
    }

    /* proxy position2d -> assuming position2d1 is VFH / ND */
    position2d = playerc_position2d_create(client, 1);
    if (playerc_position2d_subscribe(position2d, PLAYERC_OPEN_MODE) != 0) {
        fprintf(stderr, "Error subscribing: %s\n", playerc_error_str());
        return -1;
    }

    playerc_position2d_enable(position2d, 1);

    /* Send the position to the robot */
    playerc_position2d_set_cmd_pose(position2d, gx, gy, ga, &state);

    // small sleep just in case
    usleep(1000000);
    while (1) {
	playerc_client_read(client);
        double px = position2d->px;
        double py = position2d->py;
        double pa = position2d->pa;

        double dx = gx - px;
        double dy = gy - py;
        double dist = sqrt(dx*dx + dy*dy);
        double ang_err = atan2(sin(ga - pa), cos(ga - pa));

        
        if (dist <= pos_tol && fabs(ang_err) <= ang_tol) {
            printf("Objective reached!\n");
            break;
        }

        /* DEBUGGING */
        printf("position : %f %f %f\n", px, py, pa);
        printf("goal     : %f %f %f\n", gx, gy, ga);
        printf("error    : %f %f\n\n", dist, ang_err);

        /* sendind the objective over again seems to have a better performance */
        playerc_position2d_set_cmd_pose(position2d, gx, gy, ga, &state);

        usleep(100000);
    }

    /* Clear Player */
    playerc_position2d_unsubscribe(position2d);
    playerc_position2d_destroy(position2d);
    playerc_client_disconnect(client);
    playerc_client_destroy(client);

    return 0;
}
