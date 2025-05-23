if (feedback != NULL) {
        fclose(feedback);
        printf("File feedback berhasil direset (kosong).\n");
    } else {
        printf("Gagal membuka file feedback.\n");
    }