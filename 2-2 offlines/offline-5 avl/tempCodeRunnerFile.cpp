  auto start_time = chrono::high_resolution_clock::now();

                obj.root = obj.insert(obj.root, new_node);
                auto end_time = chrono::high_resolution_clock::now();
                double time_taken = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() / 1000.0;
                insert_time += time_taken;