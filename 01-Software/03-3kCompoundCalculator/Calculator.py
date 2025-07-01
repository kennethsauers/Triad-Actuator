def calculate_torque_reduction(z_R1, z_S, z_P1, z_P2, z_R2, T_in):
    # Calculate G1
    G1 = z_R1 / z_S

    # Calculate G2
    G2 = (z_P2 * z_R1) / (z_P1 * z_R2)

    # Calculate total transmission ratio i_T
    i_T = (1 + G1) / (1 - G2)

    # Output torque (ignoring losses, so torque scales with ratio)
    T_out = T_in * i_T

    return i_T, T_out

# Example usage:
z_R1 = 60
z_S = 12
z_P1 = 24
z_P2 = 20
z_R2 = 56
T_in = 1  # Input torque in Nm

i_T, T_out = calculate_torque_reduction(z_R1, z_S, z_P1, z_P2, z_R2, T_in)

print(f"Transmission Ratio (i_T): {i_T:.2f}")
print(f"Output Torque (T_out): {T_out:.2f} Nm")
