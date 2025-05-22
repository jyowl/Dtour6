top_up = fopen("top_up.dat", "ab");
    if (!top_up) {                       
        perror("File tidak bisa dibuka");
        return;
    }

    float nominal;
    printf("\nMasukkan nominal saldo yang akan di-top-up (Rp): ");
    if (scanf("%f", &nominal) != 1 || nominal <= 0) {
        puts("Nominal tidak valid – proses dibatalkan.");
        fclose(top_up);
        while (getchar() != '\n');
        return;
    }
    getchar();

    struct TopUp rek;
    rek.nominal = nominal;
    if (fwrite(&rek, sizeof(struct TopUp), 1, top_up) != 1) {
        puts("Gagal menyimpan data top-up!");
    } else {
        printf("Tekan Enter untuk kembali ke menu user...\n");
        system("cls");
        system("pause");
        printf("Top-up sebesar Rp %.2f berhasil disimpan.\n", nominal);
    }