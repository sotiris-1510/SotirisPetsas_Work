#include <stdio.h>
#include <time.h>
#include <stdlib.h>


/* --- ALGORITHM 1: RANDOM COVERAGE ---
   Selects sets randomly until k sets are chosen or the universe U is fully covered.
   Includes an 'attempts' counter to prevent infinite loops if no new coverage can be found. */

int * randomCoverage(int n, int m, int c, int k, int* U, int** poi, int* result_count) {
    int count = 0;
    int totalCovered = 0;
    int *coverage = malloc(k * sizeof(int));    // Stores the indices of the selected sets
    int *covered = calloc(n + 1, sizeof(int));    // Tracks which elements of U are covered
    *result_count = 0;

    int attempts = 0;
    while (count < k && totalCovered < n && attempts < m) {  // Limit attempts to m to avoid infinite loops
        int r = rand() % m;
        int provides_new = 0;
        attempts++;

        for (int j = 0; j < c; j++) {   // Check each element in the randomly selected set
            if (poi[r][j] == -1) break;
            if (covered[poi[r][j]] == 0) {
                provides_new = 1;
                break;
            }
        }

        if (provides_new) {   // If the set provides new coverage, add it to the solution
            coverage[count++] = r;
            attempts = 0;
            for (int j = 0; j < c; j++) {
                if (poi[r][j] == -1) break;
                if (covered[poi[r][j]] == 0) {
                    covered[poi[r][j]] = 1;
                    totalCovered++;
                }
            }
        }
    }

    *result_count = count;

    if (totalCovered < n) {   // If we couldn't cover the entire universe, return NULL
        free(covered);
        free(coverage); 
        *result_count = 0; 
        return NULL; 
    }

    *result_count = count;
    free(covered);

    return coverage;
}

/* --- ALGORITHM 2: GREEDY MAX COVERAGE ---
   Logic: In each step, pick the set with the MAXIMUM number of uncovered elements.*/

int* maxCoverage(int n, int m, int c, int k, int* U, int** poi, int* result_count) {
    int count = 0;
    int totalCovered = 0;
    int *coverage = (int*)malloc(k * sizeof(int));   // Stores the indices of the selected sets
    int *covered = (int*)calloc(n + 1, sizeof(int)); // Track elements 1 to n
    int *selected_sets = (int*)calloc(m, sizeof(int)); // Track used sets

    while (count < k && totalCovered < n) {   // Loop until we have selected k sets or covered the entire universe
        int best_index = -1;
        int max_new_points = -1;

        for (int i = 0; i < m; i++) {   // Iterate through all sets to find the one that provides the most new coverage
            if (selected_sets[i]) 
                continue;

            int current_new_points = 0;
            for (int j = 0; j < c; j++) {   // Check each element in the set to count how many new elements it would cover
                int element = poi[i][j];
                
                // Skip empty slots (0) or invalid elements
                if (element <= 0 || element > n) continue;

                if (covered[element] == 0) {
                    current_new_points++;
                }
            }

            if (current_new_points > max_new_points) {  // If this set provides more new coverage than the best found so far, update our best choice
                max_new_points = current_new_points;
                best_index = i;
            }
        }

        if (best_index == -1 || max_new_points == 0)   // If no set can provide new coverage, we are done and
            break;

        coverage[count++] = best_index;
        selected_sets[best_index] = 1;

        for (int j = 0; j < c; j++) {   // Mark the elements covered by the newly selected set
            int element = poi[best_index][j];
            if (element > 0 && element <= n) {
                if (covered[element] == 0) {
                    covered[element] = 1;
                    totalCovered++;
                }
            }
        }
    }

    *result_count = count;
    free(covered);
    free(selected_sets);

    if (totalCovered < n) {   // If we couldn't cover the entire universe, return NULL
        free(coverage);
        *result_count = 0;
        return NULL;
    }

    return coverage;
}

/* --- ALGORITHM 3: MIN SIZE GREEDY ---
   Strategy: In each iteration this algorithm picks the smallest set that provides at least one new element.
   This is often used to test if smaller sets can lead to more efficient coverage. */

int* min_size(int n, int m, int c, int k, int* U, int** S, int* result_count) {
    int* coverage = (int*)malloc(k * sizeof(int));   // Stores the indices of the selected sets
    int *is_covered = (int*)calloc(n + 1, sizeof(int));   // Tracks which elements of U are covered
    int *selected_sets = (int*)calloc(m, sizeof(int));   // Tracks which sets have been selected
 
    int total_covered_count = 0;
    *result_count = 0;

    while (*result_count < k && total_covered_count < n) {   // Loop until we have selected k sets or covered the entire universe
        int best_index = -1;
        int min_val = 1000000;

        for (int i = 0; i < m; i++) {   // Iterate through all sets to find the smallest set that provides at least one new element
            if (selected_sets[i] == 1) 
                continue; 

            int provides_new = 0;
            int current_set_size = 0;

            for (int j = 0; j < c; j++) {   // Check each element in the set to determine its size and whether it provides new coverage
                if (S[i][j] == -1) 
                    break;
                current_set_size++;

                if (is_covered[S[i][j]] == 0) 
                    provides_new = 1;
            }

            if (provides_new && current_set_size < min_val) {  // If this set provides new coverage and is smaller than the best found so far, update our best choice
                min_val = current_set_size;
                best_index = i;
            }
        }

        if (best_index == -1) 
            break;

        coverage[(*result_count)++] = best_index;
        selected_sets[best_index] = 1;

        for (int j = 0; j < c; j++) {   // Mark the elements covered by the newly selected set
            if (S[best_index][j] == -1) 
                break;
            if (is_covered[S[best_index][j]] == 0) {
                is_covered[S[best_index][j]] = 1;
                total_covered_count++;
            }
        }
    }

    free(is_covered);
    free(selected_sets);

    if (total_covered_count < n) {   // If we couldn't cover the entire universe, return NULL
        free(coverage);
        *result_count = 0;
        return NULL;
    }

    return coverage;
}

/* --- ALGORITHM 4: MAX DENSITY GREEDY ---
   Strategy: This algorithm picks the set with the highest density.
   Density = (number of new elements) / (total size of the set).
   This aims to maximize the "value for money" for each set added. */

int* max_density(int n, int m, int c, int k, int* U, int** S, int* result_count) {
    int* coverage = (int*)malloc(k * sizeof(int));    // Stores the indices of the selected sets
    int *is_covered = (int*)calloc(n + 1, sizeof(int));   // Tracks which elements of U are covered
    int *selected_sets = (int*)calloc(m, sizeof(int));   // Tracks which sets have been selected

    int total_covered_count = 0;
    *result_count = 0;

    while (*result_count < k && total_covered_count < n) {   // Loop until we have selected k sets or covered the entire universe
        int best_index = -1;
        double max_dens = -1.0; 

        for (int i = 0; i < m; i++) {   // Iterate through all sets to find the one with the highest density
            if (selected_sets[i] == 1) 
                continue;

            int new_elements_count = 0;
            int current_set_size = 0;

            for (int j = 0; j < c; j++) {   // Check each element in the set to count how many new elements it would cover and determine the size of the set
                if (S[i][j] == -1) 
                break;
                current_set_size++; 
                if (is_covered[S[i][j]] == 0) 
                    new_elements_count++;
            }

            if (new_elements_count > 0) {   // If this set provides new coverage, calculate its density and compare it to the best found so far
                double current_density = (double)new_elements_count / current_set_size;
                if (current_density > max_dens) {
                    max_dens = current_density;
                    best_index = i;
                }
            }
        }

        if (best_index == -1) 
            break;

        coverage[(*result_count)++] = best_index;
        selected_sets[best_index] = 1;

        for (int j = 0; j < c; j++) {   // Mark the elements covered by the newly selected set
            if (S[best_index][j] == -1) 
                break;
            if (is_covered[S[best_index][j]] == 0) {
                is_covered[S[best_index][j]] = 1;
                total_covered_count++;
            }
        }
    }

    free(is_covered);
    free(selected_sets);

    if (total_covered_count < n) {   // If we couldn't cover the entire universe, return NULL
        free(coverage);
        *result_count = 0;
        return NULL;
    }

    return coverage;
}

/* --- INSTANCE GENERATOR ---
   Creates a random instance of the problem.
   Elements are valued 1 to n. Sets end with -1 for variable sizes. */

void generate_random_instance(int n, int m, int c, int* U, int** S) {
    for (int i = 0; i < n; i++) {  // Fill the universe U with values from 1 to n
        U[i] = i + 1;
    }

    printf("  Filling %d sets with random data...\n", m);
    fflush(stdout);

    for (int i = 0; i < m; i++) {   // Generate each set with a random size and random elements
        if (i % 50000 == 0 && i > 0) {
            printf("    ...generated %d sets...\n", i);
            fflush(stdout);
        }

        int current_size = (rand() % c) + 1; 
        for (int j = 0; j < c; j++) {   // Fill the set with random elements from 1 to n, and end with -1 if we exceed the current size
            if (j < current_size) {
                S[i][j] = (rand() % n) + 1;
            } else {
                S[i][j] = -1; 
            }
        }
    }
    printf("  Instance generation complete!\n");
    fflush(stdout);
}

/* --- CORRECTNESS CHECK ---
   Manually recalculates the total unique coverage of a returned solution.
   Used to verify that the algorithm's reported 'totalCovered' is accurate. */

int calculate_coverage(int n, int c, int** S, int* res, int res_cnt) {
    if (res == NULL || res_cnt <= 0) return 0;

    char* covered = (char*)calloc(n + 1, sizeof(char)); 
    int total = 0;

    for (int i = 0; i < res_cnt; i++) {   // Iterate through the selected sets and mark the elements they cover
        int idx = res[i];
        for (int j = 0; j < c; j++) {
            int element = S[idx][j];
            if (element >= 1 && element <= n) { 
                if (covered[element] == 0) {
                    covered[element] = 1;
                    total++;
                }
            }
        }
    }

    free(covered);

    return total;
}

int main() {

    int flag = 1;  // 0: RUN FROM FILE, 1: RUN EXPERIMENTS

    if (flag == 0) {
        // --- READING INSTANCE FROM FILE ---
        FILE *file = fopen("sets.dat", "r");
        if (file == NULL) {
            printf("Error: To arxeio sets.dat den vrethike.\n");
            return 1;
        }

        int n, m, c, k;

        if (fscanf(file, "%d %d %d %d", &n, &m, &c, &k) != 4) return 1;

        int *U = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            fscanf(file, "%d", &U[i]);
        }

        int **S = (int **)malloc(m * sizeof(int *));
        char line[2048]; 
    
        fgets(line, sizeof(line), file); 

        for (int i = 0; i < m; i++) {
            S[i] = (int *)malloc(c * sizeof(int));
            for (int j = 0; j < c; j++) S[i][j] = 0; 

            if (fgets(line, sizeof(line), file)) {
                char *ptr = line;
                int j = 0;
                int val, offset;
                
                while (sscanf(ptr, "%d%n", &val, &offset) == 1 && j < c) {
                    S[i][j] = val;
                    ptr += offset;
                    j++;
                }
            }
        }

        fclose(file);

        int result_count;
        clock_t start, end;
        double time_ms;

        // --- EXECUTING ALGORITHM 1 ---
        start = clock();
        int* res1 = randomCoverage(n, m, c, k, U, S, &result_count);
        end = clock();
        time_ms = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;

        printf("Algo 1 (Random) Time: %.4f ms\n", time_ms);
        if (res1 == NULL) {
            printf("Algo 1: Empty Set (No coverage found)\n\n");  
        } else {
            printf("Algo 1: Found coverage with %d sets.\n\n", result_count);
            printf("Chosen Set Indices: ");

            for (int i = 0; i < result_count; i++) {
                printf("%d ", res1[i]); 
            }

            printf("\n\n");
            free(res1);
        }

        // --- EXECUTING ALGORITHM 2 ---
        start = clock();
        int* res2 = maxCoverage(n, m, c, k, U, S, &result_count);
        end = clock();
        time_ms = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC; 

        printf("Algo 2 (Maximum Coverage) Time: %.4f ms\n", time_ms);
        if (res2 == NULL) {
            printf("Algo 2: Empty Set (No coverage found)\n\n"); 
        } else {
            printf("Algo 2: Found coverage with %d sets.\n\n", result_count);
             printf("Chosen Set Indices: ");

            for (int i = 0; i < result_count; i++) {
                printf("%d ", res2[i]); 
            }

            printf("\n\n");
            free(res2);
        }

        // --- EXECUTING ALGORITHM 3 ---
        start = clock();
        int* res3 = min_size(n, m, c, k, U, S, &result_count);
        end = clock();
        time_ms = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC; 

        printf("Algo 3 (Min Size) Time: %.4f ms\n", time_ms);
        if (res3 == NULL) {
            printf("Algo 3: Empty Set (No coverage found)\n\n"); 
        } else {
            printf("Algo 3: Found coverage with %d sets.\n\n", result_count);
            printf("Chosen Set Indices: ");

            for (int i = 0; i < result_count; i++) {
                printf("%d ", res3[i]); 
            }

            printf("\n\n");

            free(res3);
        }

        // --- EXECUTING ALGORITHM 4 ---
        start = clock();
        int* res4 = max_density(n, m, c, k, U, S, &result_count);
        end = clock();
        time_ms = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;

        printf("Algo 4 (Max Density) Time: %.4f ms\n", time_ms);
        if (res4 == NULL) {
            printf("Algo 4: Empty Set (No coverage found)\n\n"); 
        } else {
            printf("Algo 4: Found coverage with %d sets.\n\n", result_count);
            printf("Chosen Set Indices: ");

            for (int i = 0; i < result_count; i++) {
                printf("%d ", res4[i]); 
            }

            printf("\n\n");
            free(res4);
        }

        // memory cleanup
        for (int i = 0; i < m; i++) 
            free(S[i]);
            
        free(S);
        free(U);
    }
    else if (flag == 1) {
        srand(time(NULL));

        int* (*algos[4])(int, int, int, int, int*, int**, int*) = {
            randomCoverage,maxCoverage, min_size, max_density
        };

        char* algo_names[] = {"Algo 1 (Random)", "Algo 2 (Max Cov)", "Algo 3 (Min Size)", "Algo 4 (Max Density)"};

        int flag2 = 3;    // 1: EXPERIMENT 1, 2: EXPERIMENT 2, 3: EXPERIMENT 3

        if (flag2 == 1) {
            // --- EXPERIMENT 1 ---
            int n1 = 30000000; 
            int m1 = 15000000; 
            int c1 = 5;

            // --- FLAT MEMORY ALLOCATION ---
            int *U1 = (int *)malloc(n1 * sizeof(int));
            int **S1 = (int **)malloc(m1 * sizeof(int *));
            int *all_data = (int *)malloc((long long)m1 * c1 * sizeof(int));

            if (U1 == NULL || S1 == NULL || all_data == NULL) {
                printf("Error: Could not allocate enough RAM.\n");
                return 1;
            }

            for (int i = 0; i < m1; i++) {
                S1[i] = &all_data[i * c1];
            }

            printf("Memory allocated. Generating random instance...\n");
            fflush(stdout);
            generate_random_instance(n1, m1, c1, U1, S1);
            printf("Instance ready. Beginning Experiment 1.\n\n");
            fflush(stdout);

            int* (*algos[4])(int, int, int, int, int*, int**, int*) = {
                randomCoverage, maxCoverage, min_size, max_density
            };

            double target_ms = 1200000.0; // 20 minutres in milliseconds

            for (int a = 0; a < 4; a++) {
                printf(">>> Analyzing %s <<<\n", algo_names[a]);
                fflush(stdout);

                int low = 1, high = m1, current_k = 1, limit_k = m1;

                // --- PHASE 1: EXPONENTIAL SEARCH TO FIND APPROXIMATE K ---
                while (current_k <= m1) {
                    int res_cnt = 0;
                    clock_t start = clock();
                    int* res = algos[a](n1, m1, c1, current_k, U1, S1, &res_cnt);
                    clock_t end = clock();

                    int coverage = calculate_coverage(n1, c1, S1, res, res_cnt);

                    double time_ms = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;

                    printf("  [Step] k = %-8d | Time: %10.2f ms | Coverage: %d\n", current_k, time_ms, coverage);
                    fflush(stdout);

                    if (res) free(res);

                    if (time_ms >= target_ms) {
                        high = current_k;
                        low = current_k / 2;
                        printf("  Target reached. Searching between %d and %d...\n", low, high);
                        fflush(stdout);
                        break;
                    }

                    if (current_k == m1) 
                        break;
                    if (current_k > m1 / 2) 
                        current_k = m1;
                    else 
                        current_k *= 2;
                }

                // --- PHASE 2: BINARY SEARCH TO FIND PRECISE K ---
                if (high > low && high < m1) {
                    while (low <= high) {
                        int mid = low + (high - low) / 2;
                        int res_cnt = 0;
                        clock_t start = clock();
                        int* res = algos[a](n1, m1, c1, mid, U1, S1, &res_cnt);
                        clock_t end = clock();

                        int coverage = calculate_coverage(n1, c1, S1, res, res_cnt);

                        double time_ms = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;

                        printf("  [Step] k = %-8d | Time: %10.2f ms | Coverage: %d\n", current_k, time_ms, coverage);
                        fflush(stdout);

                        if (res) free(res);

                        if (time_ms >= target_ms - 5000.0 && time_ms <= target_ms + 5000.0) {
                            limit_k = mid;
                            break;
                        }
                        if (time_ms < target_ms) {
                            low = mid + 1;
                            limit_k = mid;
                        } else {
                            high = mid - 1;
                        }
                    }
                }
                printf(">>> %s FINAL RESULT: 20 mins limit at k = %d <<<\n\n", algo_names[a], limit_k);
                fflush(stdout);
            }

            // memory cleanup
            free(all_data);
            free(S1);
            free(U1);
        }
        else if (flag2 == 2) {
            // --- EXPERIMENT 2 ---
            printf("\n--- STARTING EXPERIMENT 2: 10 RUNS PER ALGORITHM ---\n");
            fflush(stdout);

            int n2 = 300000, m2 = 150000, c2 = 100, k2 = 5000;

            // --- FLAT MEMORY ALLOCATION ---
            int *U2 = (int *)malloc(n2 * sizeof(int));
            int **S2 = (int **)malloc(m2 * sizeof(int *));
            int *all_data2 = (int *)malloc((long long)m2 * c2 * sizeof(int));

            if (U2 == NULL || S2 == NULL || all_data2 == NULL) {
                printf("Error: Memory allocation failed for Exp 2\n");
                return 1;
            }

            for (int i = 0; i < m2; i++) 
                S2[i] = &all_data2[i * c2];

            generate_random_instance(n2, m2, c2, U2, S2);
            printf("Instance for Experiment 2 generated. Starting runs...\n");
            fflush(stdout);

            for (int a = 0; a < 4; a++) {
                printf("\n>> Testing %s (10 runs):\n", algo_names[a]);
                fflush(stdout);

                for (int run = 1; run <= 10; run++) {
                    int res_cnt = 0;
                    clock_t start = clock();
        
                    int* res = algos[a](n2, m2, c2, k2, U2, S2, &res_cnt);
                    
                    clock_t end = clock();

                    int cov = calculate_coverage(n2, c2, S2, res, res_cnt);

                    double time_ms = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;
                    double time_mins = time_ms / 60000.0;

                    printf("   Run %2d: %10.2f ms | Coverage: %-8d | (%.2f mins)\n", run, time_ms, cov, time_mins);
                    fflush(stdout);

                    if (res) free(res);
                }
            }

            // memory cleanup
            free(all_data2); free(S2); free(U2);
        }
        else if (flag2 == 3) {
            // --- EXPERIMENT 3 ---
            printf("\n--- STARTING EXPERIMENT 3: SOLUTION SIZE VS N ---\n");
            int n_vals[] = {50,100,200,500,1000,1500,2000,2500,3000,4000,5000,7500,10000};
            
            for (int i = 0; i < 13; i++) {
                int cur_n = n_vals[i];
                int cur_m = 2*n_vals[i]; 
                int cur_c = cur_n/5; 
                int cur_k = cur_m; 

                printf("Testing n = %d:\n", cur_n);
                
                double avg_size[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

                for (int run = 0; run < 5; run++) {
                    int *U3 = malloc(cur_n * sizeof(int));
                    int **S3 = malloc(cur_m * sizeof(int *));
                    for(int j=0; j<cur_m; j++)
                        S3[j] = malloc(cur_c * sizeof(int));
                    
                    generate_random_instance(cur_n, cur_m, cur_c, U3, S3);
                    
                    for (int a = 0; a < 4; a++) {
                        int res_cnt = 0;
                        int* res = algos[a](cur_n, cur_m, cur_c, cur_k, U3, S3, &res_cnt);

                        if (res) {
                            avg_size[a] += res_cnt;
                            free(res);
                        }
                    }
                    
                    // memory cleanup for this run
                    for(int j=0; j<cur_m; j++) 
                        free(S3[j]); 
                        
                    free(S3); 
                    free(U3);
                }
                
                for (int a = 0; a < 4; a++) {
                    printf("  %s -> Avg Solution Size: %.2f sets\n", algo_names[a], avg_size[a]/5.0);
                }

                printf("----------------------------\n");
            }
        }
    }

    return 0;
    
}