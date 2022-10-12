enum class BrushType : int
{
  GRAB,
  SCALE,
  TWIST,
  PINCH
};

class RegularizedKelvinlets {
    public:
    const double dt = 0.1;
    const double Ps = 0.5;
    const double Ym = 1.0;
    const double a = 1/(4*3.1415926*Ym);
    const double b = a/(4*(1-Ps));
    const double c = 2/(3*a-2*b);
    Eigen::MatrixX3d V;
    const double epsilon = 1e-5;

    RegularizedKelvinlets(const Eigen::MatrixX3d& OV_): V(OV_) {}

    void compute(BrushType brush_type = BrushType::GRAB, Eigen::Vector3d x0 = Eigen::Vector3d::Zero(), Eigen::Matrix3d force = Eigen::Matrix3d::Identity()) {
        const Eigen::MatrixX3d r = V.rowwise()-x0.transpose();
        const Eigen::VectorXd r_sqrd_norm = r.rowwise().squaredNorm();
        const double sqrd_epsilon = std::pow(epsilon,2);
        const Eigen::ArrayXd r_epsilon = ((r_sqrd_norm.array() + sqrd_epsilon).sqrt());
        const Eigen::ArrayXd r_epsilon_3_inv = r_epsilon.pow(3).inverse();
        const Eigen::ArrayXd r_epsilon_5_inv = r_epsilon.pow(5).inverse();
        Eigen::MatrixXd dE;
        dE.resizeLike(V);
        switch (brush_type) {
            case BrushType::GRAB: {

            } break;
            case BrushType::TWIST: {
                dE = -a * (((force*r.transpose()).transpose()).array().colwise() * (r_epsilon_3_inv+(3*sqrd_epsilon*2)*r_epsilon_5_inv)).matrix();
            } break;
            case BrushType::SCALE: {
                const double s = -5;
                dE = -(2.*b-a) * ((s*r).array().colwise() * (r_epsilon_3_inv+(3*sqrd_epsilon*2)*r_epsilon_5_inv)).matrix();
            } break;
            case BrushType::PINCH: {
                dE = (2.*b-a) * (((force*r.transpose()).transpose()).array().colwise()*r_epsilon_3_inv).matrix() - 
                     (3./2.*
                        (((2*b*(r.transpose()*(force*r.transpose()).transpose())+
                        a*sqrd_epsilon*force)*r.transpose()).transpose().array().colwise()
                    *r_epsilon_5_inv).matrix());
            } break;
            default:
            break;
        }
        V += dt * dE;
    }

    void reset(const Eigen::MatrixX3d& V_) {
        V = V_;
    }
};
