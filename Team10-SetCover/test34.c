#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int* min_size(int n, int m, int c, int k, int* U, int** S, int* result_count) {
    // Δέσμευση μνήμης για τον πίνακα αποτελεσμάτων (μέγεθος k) 
    int* coverage = (int*)malloc(k * sizeof(int));
    
    // Βοηθητικοί πίνακες για να ξέρουμε τι καλύψαμε και τι επιλέξαμε 
    int is_covered[n + 1]; // Πίνακας flags για τα στοιχεία του U
    int selected_sets[m];  // Πίνακας flags για τους δρομολογητές S

    for(int i=0; i<=n; i++) 
        is_covered[i] = 0;

    for(int i=0; i<m; i++) 
        selected_sets[i] = 0;

    int total_covered_count = 0;
    *result_count = 0;

    // Κύριο Loop: Συνεχίζει μέχρι να καλυφθούν όλα (n) ή να φτάσουμε τα k σύνολα 
    while (*result_count < k && total_covered_count < n) {
        int best_index = -1;
        int min_size = 1000000; // Αρχικοποίηση με έναν πολύ μεγάλο αριθμό

        // Εσωτερικό Loop: Ψάχνουμε σε όλους τους m δρομολογητές
        for (int i = 0; i < m; i++) {
            if (selected_sets[i] == 1) continue; // Αν τον επιλέξαμε ήδη, προσπέρασε τον

            int provides_new = 0;
            int current_set_size = 0;

            // Έλεγχος στοιχείων του συγκεκριμένου δρομολογητή S[i] 
            for (int j = 0; j < c; j++) {
                if (S[i][j] == -1) break; // Τέλος των στοιχείων αυτού του δρομολογητή
                
                current_set_size++; // Μετράμε το συνολικό μέγεθος |Si| 
                
                // Ελέγχουμε αν το στοιχείο S[i][j] είναι "νέο"
                if (is_covered[S[i][j]] == 0) {
                    provides_new = 1; 
                }
            }

            // Κριτήριο Επιλογής: Πρέπει να δίνει νέο στοιχείο και να είναι το μικρότερο 
            if (provides_new == 1) {
                if (current_set_size < min_size) {
                    min_size = current_set_size;
                    best_index = i;
                } 
                // Αν υπάρχει ισοπαλία στο μέγεθος, ο κώδικας κρατά τον μικρότερο δείκτη (index) 
            }
        }

        // Αν δεν βρέθηκε κανένας δρομολογητής που να προσφέρει νέα κάλυψη, σταμάτα 
        if (best_index == -1) break;

        // Ενημέρωση καταστάσεων: Πρόσθεσε τον δρομολογητή στο Coverage
        coverage[*result_count] = best_index;
        (*result_count)++;
        selected_sets[best_index] = 1;

        // Μαρκάρουμε τα στοιχεία του ως καλυμμένα πλέον
        for (int j = 0; j < c; j++) {
            if (S[best_index][j] == -1) break;
            if (is_covered[S[best_index][j]] == 0) {
                is_covered[S[best_index][j]] = 1;
                total_covered_count++;
            }
        }
    }

    // Τελικός Έλεγχος: Αν δεν καλύφθηκαν όλα τα n στοιχεία, επέστρεψε κενό σύνολο
    if (total_covered_count < n) {
        free(coverage);
        *result_count = 0;
        return NULL;
    }

    return coverage;
}

int* max_density(int n, int m, int c, int k, int* U, int** S, int* result_count) {
    // Δέσμευση μνήμης για την κάλυψη
    int* coverage = (int*)malloc(k * sizeof(int));
    
    // Πίνακες ελέγχου
    int is_covered[n + 1]; 
    int selected_sets[m];
    for(int i=0; i<=n; i++) is_covered[i] = 0;
    for(int i=0; i<m; i++) selected_sets[i] = 0;

    int total_covered_count = 0;
    *result_count = 0;

    // Κύριο Loop: Μέχρι k σύνολα ή n στοιχεία 
    while (*result_count < k && total_covered_count < n) {
        int best_index = -1;
        double max_density = -1.0; // Χρησιμοποιούμε double για τη διαίρεση

        // Αναζήτηση σε όλους τους m δρομολογητές 
        for (int i = 0; i < m; i++) {
            if (selected_sets[i] == 1) continue;

            int new_elements_count = 0;
            int current_set_size = 0;

            // Μέτρηση νέων στοιχείων και συνολικού μεγέθους 
            for (int j = 0; j < c; j++) {
                if (S[i][j] == -1) break;
                
                current_set_size++; // Sinoliko megethos |Si|
                
                if (is_covered[S[i][j]] == 0) {
                    new_elements_count++; // Monon ta nea mh-kalymmena 
                }
            }

            // Υπολογισμός Πυκνότητας: density = (νέα) / (συνολικό μέγεθος) 
            if (new_elements_count > 0) {
                double current_density = (double)new_elements_count / current_set_size;

                // Επιλογή της μέγιστης πυκνότητας [cite: 26]
                if (current_density > max_density) {
                    max_density = current_density;
                    best_index = i;
                }
                // Σε περίπτωση ισοπαλίας, ο κώδικας κρατά τον μικρότερο δείκτη (i) 
            }
        }

        // Αν κανένα σύνολο δεν προσφέρει νέα κάλυψη, σταμάτα 
        if (best_index == -1) break;

        // Προσθήκη του καλύτερου συνόλου [cite: 59]
        coverage[*result_count] = best_index;
        (*result_count)++;
        selected_sets[best_index] = 1;

        // Ενημέρωση των στοιχείων που καλύφθηκαν
        for (int j = 0; j < c; j++) {
            if (S[best_index][j] == -1) break;
            if (is_covered[S[best_index][j]] == 0) {
                is_covered[S[best_index][j]] = 1;
                total_covered_count++;
            }
        }
    }

    // Έλεγχος αν η κάλυψη είναι πλήρης 
    if (total_covered_count < n) {
        free(coverage);
        *result_count = 0;
        return NULL; // Επιστροφή κενού συνόλου 
    }

    return coverage;
}

void generate_random_instance(int n, int m, int c, int* U, int** S) {
    // Γέμισμα του U με τα στοιχεία 1 έως n 
    for (int i = 0; i < n; i++) {
        U[i] = i + 1;
    }

    // Γέμισμα των m δρομολογητών με τυχαία σημεία ενδιαφέροντος 
    for (int i = 0; i < m; i++) {
        // Επιλογή τυχαίου πλήθους στοιχείων για τον δρομολογητή (έως c) 
        int current_size = (rand() % c) + 1; 
        
        for (int j = 0; j < c; j++) {   
            if (j < current_size) {
                // Τυχαίο σημείο ενδιαφέροντος από το σύνολο U (1 έως n) 
                S[i][j] = (rand() % n) + 1;
            } else {
                // Σήμανση κενού στοιχείου αν ο δρομολογητής καλύπτει λιγότερα από c σημεία 
                S[i][j] = -1; 
            }
        }
    }
}

int main() {
    // Flag: 0 για ανάγνωση από sets.dat, 1 για πειραματική αξιολόγηση
    int experimental_flag = 1; 

    if (experimental_flag == 0) {
        // --- ΕΛΕΓΧΟΣ ΟΡΘΟΤΗΤΑΣ --- 
        FILE *file = fopen("sets.dat", "r");
        if (file == NULL) {
            printf("Error: To arxeio sets.dat den vrethike.\n");
            return 1;
        }

        int n, m, c, k;
        // 1η γραμμή: n (στοιχεία U), m (δρομολογητές), c (max στοιχεία ανά S), k (max δρομολογητές)
        if (fscanf(file, "%d %d %d %d", &n, &m, &c, &k) != 4) return 1;

        // 2η γραμμή: Στοιχεία του συνόλου U 
        int *U = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            fscanf(file, "%d", &U[i]);
        }

        // Υπόλοιπες γραμμές: Στοιχεία των m δρομολογητών S
        int **S = (int **)malloc(m * sizeof(int *));
        for (int i = 0; i < m; i++) {
            S[i] = (int *)malloc(c * sizeof(int));
            for (int j = 0; j < c; j++) S[i][j] = -1; // Αρχικοποίηση με -1 για κενά στοιχεία
            
            for (int j = 0; j < c; j++) {
                if (fscanf(file, "%d", &S[i][j]) != 1) break;
            }
        }
        fclose(file);

        int result_count;
        clock_t start, end;
        double time_ms;

        // --- ΕΚΤΕΛΕΣΗ ΑΛΓΟΡΙΘΜΟΥ 3 ---
        start = clock();
        int* res3 = min_size(n, m, c, k, U, S, &result_count);
        end = clock();
        time_ms = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC; // Μετατροπή σε ms 

        printf("Algo 3 (Min Size) Time: %.4f ms\n", time_ms);
        if (res3 == NULL) {
            printf("Algo 3: Empty Set (No coverage found)\n\n"); // 
        } else {
            printf("Algo 3: Found coverage with %d sets.\n\n", result_count);
            free(res3);
        }

        // --- ΕΚΤΕΛΕΣΗ ΑΛΓΟΡΙΘΜΟΥ 4 ---
        start = clock();
        int* res4 = max_density(n, m, c, k, U, S, &result_count);
        end = clock();
        time_ms = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;

        printf("Algo 4 (Max Density) Time: %.4f ms\n", time_ms);
        if (res4 == NULL) {
            printf("Algo 4: Empty Set (No coverage found)\n\n"); // 
        } else {
            printf("Algo 4: Found coverage with %d sets.\n\n", result_count);
            free(res4);
        }

        // Αποδέσμευση μνήμης 
        for (int i = 0; i < m; i++) free(S[i]);
        free(S);
        free(U);

    } else {
        // --- ΠΕΙΡΑΜΑΤΙΚΗ ΑΞΙΟΛΟΓΗΣΗ ---
        int n = 100, m = 200, c = 20; // Παράδειγμα τιμών για το πείραμα 
        int *U = (int *)malloc(n * sizeof(int));
        int **S = (int **)malloc(m * sizeof(int *));
        for (int i = 0; i < m; i++) S[i] = (int *)malloc(c * sizeof(int));

        // Παραγωγή τυχαίου στιγμιοτύπου
        generate_random_instance(n, m, c, U, S);

        printf("--- Experiment 1: Increasing k ---\n");
        for (int k = 1; k <= m; k++) {
            int result_count;
            clock_t start, end;
            
            // Παράδειγμα εκτέλεσης για τον Αλγόριθμο 4
            start = clock();
            int* res4 = max_density(n, m, c, k, U, S, &result_count);
            end = clock();
            
            double time_ms = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;
            printf("k=%d | Time: %.2f ms | Status: %s\n", k, time_ms, (res4 ? "Success" : "No Coverage"));

            if (res4 != NULL) free(res4);

            // Έλεγχος ορίου 20 λεπτών (20 * 60 * 1000 ms) 
            if (time_ms > 1200000) {
                printf("Algorithm 4 exceeded 20 minutes at k=%d\n", k);
                break;
            }
        }

        // Αποδέσμευση μνήμης
        for (int i = 0; i < m; i++) free(S[i]);
        free(S);
        free(U);
    }

    return 0;
}