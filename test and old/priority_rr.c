// void calculate_priority(Process processes[], int num, int quantam){

//     int rt[num];
//     int arrived[num];
//     int completed[num];
//     int quantamcheck[num];
//     int responded[num];
//     int priorityIndex = -1, currentTime = 0, priority = INT_MAX, finishTime = 0, complete = 0, responseTime = 0;

//     for (int i = 0;i<num;i++){
//         rt[i] = processes[i].burstTime;
//         arrived[i] = 0;
//         completed[i] = 0;
//         quantamcheck[i] = 0;
//         responded[i] = 0;
//     }

//     while(complete!=num){

//         int flag = 0;

//         for (int j = 0;j<num;j++){
//             if (processes[j].arrivalTime <= currentTime && rt[j] != 0){
//                 arrived[j] = 1;
//                 flag = 1;
//             }
//         }

//         if(flag == 0){
//             currentTime++;
//             continue;
//         }

//         int firstOfPriorityFound = 0;
//         for (int j = 0;j<num;j++){
//             if (arrived[j] == 1 && processes[j].priorityId < priority && completed[j] != 1){
//                 priority = processes[j].priorityId;
//                 priorityIndex = j;
//                 firstOfPriorityFound = 1;
//             }
//             else if (arrived[j] == 1 && processes[j].priorityId == priority && completed[j] != 1 && !firstOfPriorityFound){
//                 if (quantamcheck[j] < quantam){
//                     priority = processes[j].priorityId;
//                     priorityIndex = j;
//                     firstOfPriorityFound = 1;
//                 }
//             }
            
//         }

//         if (responded[priorityIndex] == 0){
//             responseTime = currentTime - processes[priorityIndex].arrivalTime;
//             processes[priorityIndex].responseTime = responseTime;
//             responded[priorityIndex] = 1;
//         }

//         rt[priorityIndex]--;
//         currentTime++;
//         quantamcheck[priorityIndex]++;

//         int allReachedQuantum = 1;
//         for (int j = 0; j < num; j++) {
//             if (processes[j].priorityId == priority && quantamcheck[j] < quantam) {
//                 allReachedQuantum = 0;
//                 break;
//             }
//         }
//         if (allReachedQuantum) {
//             for (int j = 0; j < num; j++) {
//                 quantamcheck[j] = 0;
//             }
//         }
        
//         if (rt[priorityIndex] == 0){
//             complete++;
//             arrived[priorityIndex] = 0;
//             completed[priorityIndex] = 1;
//             finishTime = currentTime;
//             priority = INT_MAX;
//             processes[priorityIndex].turnaroundTime = finishTime - processes[priorityIndex].arrivalTime;
//             processes[priorityIndex].waitingTime = processes[priorityIndex].turnaroundTime - processes[priorityIndex].burstTime;
//         }
//     }
// }