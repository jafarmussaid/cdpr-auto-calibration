//========================================================================================================================
// Project: Cable-Driven Parallel Robots for Agile Manufacturing – CRAFT
// File: auto_calibration.c
// Author: Eng. Jaâfar Moussaid, Summer 2019
// Description: Simulation tool for an event-based autocalibration method for CDPRs using metallic marks and fixed sensors.
//========================================================================================================================

#include <stdio.h>

//--------------------------------------------------------------------------------------------------
// Constants
//--------------------------------------------------------------------------------------------------
#define D_MOY 0.45f  // [m] Average distance between successive metallic marks (d_moy)

//--------------------------------------------------------------------------------------------------
// Main Program
//--------------------------------------------------------------------------------------------------
int main()
{
    // Input parameters
    float ro_max = 0.0f;     // Maximum cable length [m]
    float hauteur = 0.0f;    // Vertical height of the support structure [m]
    int nombre_stations = 0; // Number of fixed sensor stations

    // Output variables
    int nombre_marques = 1000;                // Estimated number of marks
    int nombre_marques_necessaires = 0;       // Actual number of marks needed
    float delta_m[7] = {0.75f, 0.15f, 0.65f, 0.25f, 0.55f, 0.35f, 0.45f};  // Variable mark spacing [m]
    float delta_station[7] = {0.8f, 0.2f, 0.7f, 0.3f, 0.6f, 0.4f, 0.5f};  // Sensor spacing variation [m]

    // Arrays (with max reasonable assumptions)
    float ro[1000];              // Cable length to mark m_i
    float delta_ro[1000];        // Difference between two successive marks
    float station[100];          // Position of sensor stations
    float temps[1000][100];      // Time of passage of mark m_i through station s_j

    //--------------------------------------------------------------------------------------------------
    // Input prompt
    //--------------------------------------------------------------------------------------------------
    printf("\nEnter maximum cable length [m]: ");
    scanf("%f", &ro_max);

    printf("Enter vertical support height [m]: ");
    scanf("%f", &hauteur);

    printf("Enter number of sensor stations (2 to %.0f): ", hauteur);
    scanf("%d", &nombre_stations);

    //--------------------------------------------------------------------------------------------------
    // Compute number of marks and initial cable state
    //--------------------------------------------------------------------------------------------------
    ro[0] = ro_max - hauteur;
    nombre_marques = (int)(ro_max / D_MOY);

    printf("\nEstimated number of marks: %d\n", nombre_marques);
    printf("--------------------------------------------------------------------------\n");
    printf("|  Time [s] | Mark # |  ρᵢ [m]  | Station # | Δρᵢ [m] |\n");
    printf("--------------------------------------------------------------------------\n");

    //--------------------------------------------------------------------------------------------------
    // Simulate detection events
    //--------------------------------------------------------------------------------------------------
    for (int i = 1; i <= nombre_marques; i++) {
        for (int j = nombre_stations; j >= 1; j--) {
            // Compute cable length to current mark
            ro[i] = ro[i - 1] - delta_m[i % 7];
            delta_ro[i] = ro[i - 1] - ro[i];

            // Position of station j (non-uniform spacing)
            station[j] = hauteur / (nombre_stations - j + 1) - delta_station[(nombre_stations - j + 1) % 7];

            // Time estimation (v = 1 m/s)
            temps[i][j] = (ro_max + hauteur) - ro[i] - station[j];

            // Print detection event
            printf("| %9.2f | %6d | %8.2f | %9d | %8.2f |\n", temps[i][j], i, ro[i], j, delta_ro[i]);
        }

        // Stop if cable becomes too short
        if (ro[i] < delta_m[0]) {
            printf("--------------------------------------------------------------------------\n");
            nombre_marques_necessaires = i;
            printf("Required number of metallic marks: %d\n", nombre_marques_necessaires);
            break;
        }
    }

    //--------------------------------------------------------------------------------------------------
    // Print recommended sensor positions
    //--------------------------------------------------------------------------------------------------
    printf("\nRecommended vertical positions for sensor stations:\n");
    printf("-----------------------------------------------------------\n");
    printf("| Station # | sⱼ (Distance from winch center) [m]          |\n");
    printf("-----------------------------------------------------------\n");
    for (int j = nombre_stations; j >= 1; j--) {
        printf("| %9d | %38.2f |\n", j, station[j]);
    }
    printf("-----------------------------------------------------------\n");

    return 0;
}
