#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 檔案名稱：用來儲存 "目前賣到第幾單"
const char *COUNTER_FILE = "lotto_count.txt";

/**
 * 取得下一個彩卷編號 (Ticket ID)
 * - 會自動讀取計數器檔案, 將數字+1, 再寫回檔案
 * - 傳回 +1 後的新編號
 */
int get_next_ticket_id() {
    int count = 0;
    FILE *fp;

    // 1. 嘗試讀取舊的計數
    fp = fopen(COUNTER_FILE, "r");
    if (fp != NULL) {
        // 檔案存在, 讀取數字
        fscanf(fp, "%d", &count);
        fclose(fp);
    }
    // 如果 fp == NULL (檔案不存在), count 會維持 0 (這是第一次執行)

    // 2. 將計數 +1
    count++;

    // 3. 將新的計數寫回檔案 (覆蓋)
    fp = fopen(COUNTER_FILE, "w");
    if (fp == NULL) {
        perror("錯誤：無法寫入計數器檔案");
        exit(1); // 嚴重錯誤, 必須停止
    }
    fprintf(fp, "%d", count); // 寫入新的數字
    fclose(fp);

    // 4. 傳回這個新的編號
    return count;
}

/**
 * 產生一組 7 個不重複的號碼 (1-49)
 */
void generate_lotto_set(int set[7]) {
    int i, j;
    for (i = 0; i < 7; i++) {
        int num;
        int exists;
        do {
            num = rand() % 49 + 1; // 產生 1-49 的亂數
            exists = 0;
            // 檢查這個號碼是否已存在於此組
            for (j = 0; j < i; j++) {
                if (set[j] == num) {
                    exists = 1; // 找到了, 號碼重複
                    break;
                }
            }
        } while (exists); // 如果重複, 就重新產生
        set[i] = num; // 確定是新號碼, 存入
    }
}


int main() {
    // 1. 播種亂數種子 (只需要做一次)
    srand(time(NULL));

    // 2. 取得這一單的 ID (這個函式會自動處理檔案讀寫)
    int ticket_id = get_next_ticket_id();

    // 3. 準備輸出的檔案名稱, e.g., "lotto[00001].txt"
    char output_filename[50];
    sprintf(output_filename, "lotto[%05d].txt", ticket_id);

    // 4. 開啟這個新檔案
    FILE *out_fp = fopen(output_filename, "w");
    if (out_fp == NULL) {
        perror("錯誤：無法建立彩卷檔案");
        return 1;
    }

    // 5. 取得目前時間
    time_t now = time(0);
    struct tm *tm_info = localtime(&now);
    char time_str[100];
    // 依照圖片格式化時間 "Mon Mar  7 10:11:14 2022"
    strftime(time_str, sizeof(time_str), "%a %b %d %H:%M:%S %Y", tm_info);

    // 6. 寫入檔案內容 (根據圖片格式)
    fprintf(out_fp, "======== lotto649 ========\n");
    fprintf(out_fp, "==+ No.%05d +==\n", ticket_id); // 寫入新的單數編號
    fprintf(out_fp, "= %s =\n", time_str);       // 寫入時間

    // 7. 產生 5 組號碼
    int i, j;
    for (i = 1; i <= 5; i++) {
        int lotto_set[7];
        generate_lotto_set(lotto_set); // 產生 7 個不重複號碼

        fprintf(out_fp, "[%d]:", i);
        for (j = 0; j < 7; j++) {
            fprintf(out_fp, " %02d", lotto_set[j]);
        }
        fprintf(out_fp, "\n");
    }

    fprintf(out_fp, "======== csie@CGU ========\n");

    // 8. 關閉檔案並通知使用者
    fclose(out_fp);
    printf("已成功產生檔案: %s\n", output_filename);

    return 0;
}
