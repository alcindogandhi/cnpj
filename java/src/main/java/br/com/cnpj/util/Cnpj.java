package br.com.cnpj.util;

public final class Cnpj {
    static final byte BASE = 36;
    static final byte N = 12;

    static final byte PESO1[] = {5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
    static final byte PESO2[] = {6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};

    private static byte encodeByte(final byte b) {
        return (byte) (Character.isDigit(b) ? b - '0' : Character.toUpperCase(b) - 'A' + 10);
    }

    private static byte decodeByte(final byte b) {
        return (byte) (b < 10 ? b + '0' : b - 10 + 'A');
    }

    private static short dotProduct(final byte[] peso, final byte[] v) {
        short sum = 0;
        for (int i = 0; i < N; i++) {
            sum += peso[i] * (v[i] - '0');
        }
        return sum;
    }

    private static byte calcDv(final byte[] v) {
        int d1 = dotProduct(PESO1, v) % BASE;
        int d2 = dotProduct(PESO2, v) % BASE;
        System.out.println("D1: " + d1 + ", D2: " + d2);

        d1 = (d1 > 1) ? 11 - d1 : 0;
	    d2 += d1*PESO2[N];
	    d2 %= 11;
	    d2 = (d2 > 1) ? 11 - d2 : 0;

	    return (byte)(10*d1 + d2);
    }

    public static long encode(final String in) {
        long code = 0;
        for (final byte b : in.getBytes()) {
            code = BASE * code + encodeByte(b);
        }
        return code;
    }

    public static String decode(long code) {
        final byte[] v = new byte[N+2];
        for (int i = N - 1; i >= 0; i--) {
            v[i] = decodeByte((byte) (code % BASE));
            code /= BASE;
        }
        byte dv = calcDv(v);
        v[N] = (byte) ((dv / 10) + '0');
        v[N + 1] = (byte) ((dv % 10) + '0');
        return new String(v);
    }

    public static String removeMask(final String cnpj) {
        if (cnpj == null || cnpj.isEmpty()) {
            return "";
        }
        return cnpj.replaceAll("[^0-9A-Za-z]", "").toUpperCase();        
    }

    public static String addMask(final String cnpj) {
        return cnpj.replaceAll("(\\d{2})(\\d{3})(\\d{3})(\\d{4})(\\d{2})", "$1.$2.$3/$4-$5");
    }

    public static boolean isValid(String cnpj) {
        if (cnpj == null)
            return false;
        cnpj = removeMask(cnpj);
        if (cnpj.length() != N+2) {
            return false;
        }
        if ((!Character.isDigit(cnpj.charAt(N))) && (!Character.isDigit(cnpj.charAt(N+1)))) {
            return false;
        }
        byte dv = (byte)(10*(cnpj.charAt(N)-'0') + (cnpj.charAt(N+1)-'0'));
        System.out.println("CNPJ: " + cnpj + ", DV: " + dv + ", DV Calculado: " + calcDv(cnpj.getBytes()));
        return dv == calcDv(cnpj.getBytes());
    }
}
