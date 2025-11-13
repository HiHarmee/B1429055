#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int win_nums[3];
    int i, j;

    // 1. 提示並讀取使用者輸入的三個中獎號碼
    printf("請輸入中獎號碼三個： ");
    scanf("%d %d %d", &win_nums[0], &win_nums[1], &win_nums[2]);

    // 2. 打印確認輸入
    printf("輸入中獎號碼為： %02d %02d %02d\n", win_nums[0], win_nums[1], win_nums[2]);
    printf("以下為中獎彩卷：\n");

    // 3. 開啟 lotto.txt 檔案
    FILE *fp = fopen("lotto.txt", "r");
    if (fp == NULL) {
        perror("錯誤：無法開啟 lotto.txt");
        return 1;
    }

    char line_buffer[256];
    char date_str[100];
    int line_count = 0;

    // 4. 逐行讀取檔案
    while (fgets(line_buffer, sizeof(line_buffer), fp)) {
        line_count++;

        // 5. 處理第 2 行：讀取日期
        if (line_count == 2) {
            char d_month[20], d_day[5], d_year[10];
            // 根據範例 "======== March 13 2025 ===" 格式解析
            sscanf(line_buffer, "======== %s %s %s ===", d_month, d_day, d_year);
            sprintf(date_str, "%s %s %s", d_month, d_day, d_year);
            continue; // 繼續讀取下一行
        }

        // 6. 處理第 3 到 7 行：彩卷號碼
        if (line_count >= 3 && line_count <= 7) {
            // 檢查是否為空行 (例如: [4]: -- -- -- -- -- -- --)
            if (strstr(line_buffer, "--")) {
                continue; // 是空行，跳過
            }

            // 解析彩卷上的 7 個號碼
            char set_id_str[10]; // 用來儲存 "[1]:"
            int ticket_nums[7];
            
            // sscanf 會讀取 1 個字串 和 7 個數字
            int read_count = sscanf(line_buffer, "%s %d %d %d %d %d %d %d",
                                   set_id_str,
                                   &ticket_nums[0], &ticket_nums[1], &ticket_nums[2],
                                   &ticket_nums[3], &ticket_nums[4], &ticket_nums[5],
                                   &ticket_nums[6]);

            if (read_count != 8) {
                // 如果解析失敗 (格式不對或空行)，也跳過
                continue;
            }

            // 7. 比對號碼
            int is_winner = 0; // 標記是否中獎
            for (i = 0; i < 7; i++) { // 遍歷彩卷上的 7 個號碼
                for (j = 0; j < 3; j++) { // 遍歷使用者輸入的 3 個中獎號碼
                    if (ticket_nums[i] == win_nums[j]) {
                        is_winner = 1; // 找到了！
                        break; // 停止內層迴圈 (不需要再比對其他中獎號碼)
                    }
                }
                if (is_winner) {
                    break; // 停止外層迴圈 (已經確定這張中獎，不用再比對彩卷上剩下的號碼)
                }
            }

            // 8. 如果中獎，就印出
            if (is_winner) {
                // 移除 line_buffer 最後可能包含的換行符號
                line_buffer[strcspn(line_buffer, "\n")] = 0;
                
                // 依照範例格式印出
                printf("售出時間： %s: %s\n", date_str, line_buffer);
            }
        }
    }

    // 9. 關閉檔案
    fclose(fp);

    return 0;
}
